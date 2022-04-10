#include <fmt/chrono.h>
#include <fmt/format.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "engine/engine.hpp"
#include "game/circle_minigame.hpp"
#include "game/ring_scene.hpp"

namespace Sumo::Game {

namespace {

  bool isKeyArrowEvent(const ftxui::Event &event)
  {
    return (event == ftxui::Event::ArrowLeft || event == ftxui::Event::ArrowRight || event == ftxui::Event::ArrowUp
            || event == ftxui::Event::ArrowDown);
  }

  vec2f direction(const ftxui::Event &key_event)
  {
    if (key_event == ftxui::Event::ArrowUp) { return vec2f{ 0, -1 }; }
    if (key_event == ftxui::Event::ArrowDown) { return vec2f{ 0, 1 }; }
    if (key_event == ftxui::Event::ArrowLeft) { return vec2f{ -1, 0 }; }
    if (key_event == ftxui::Event::ArrowRight) { return vec2f{ 1, 0 }; }
    return vec2f{ 0, 0 };
  }
}// namespace

RingScene::RingScene()
{
  m_player1.position = p1_starting_pos;
  m_player2.position = p2_starting_pos;

  // let's allow player1 to be slightly faster?
  m_player2.speed = 0.8F * m_player1.speed;// NOLINT magic numbers

  m_player1_controller = PlayerController{};
  m_player1_controller.event_handler = ftxui::CatchEvent([this](const ftxui::Event &event) {
    using namespace std::chrono_literals;
    static constexpr milliseconds keyboard_timeout = 300.0ms;

    std::chrono::steady_clock::time_point event_time = std::chrono::steady_clock::now();

    auto dt = std::chrono::duration_cast<milliseconds>(event_time - m_player1_controller.last_event.key_time);

    if (m_in_minigame && event == ftxui::Event::Character(' ')) {
      m_minigame.check();
      return true;
    }

    if (!isKeyArrowEvent(event)) {
      if (isKeyArrowEvent(m_player1_controller.last_event.event)) {
        return false;
      } else {
        if (dt.count() > keyboard_timeout.count()) {
          m_player1.velocity = { 0, 0 };
          return false;
        }
      }
    } else {
      m_player1_controller.last_event.key_event = event;
      m_player1_controller.last_event.key_time = event_time;
      m_player1.velocity = m_player1.speed * direction(event);
    }

    return false;
  });
}

void RingScene::update(const milliseconds dt)
{
  // maybe move this to clock or to other function
  static constexpr float milliseconds_to_seconds = 0.001F;
  const auto tick = milliseconds_to_seconds * static_cast<float>(dt.count());

  if (m_in_minigame) {
    updateMinigame(tick);
  } else {
    updatePlayers(tick);
  }
}

std::vector<GameScene::DrawableEntity> RingScene::drawableEntities()
{
  std::vector<GameScene::DrawableEntity> entities;

  entities.emplace_back(m_groundSprite, vec2u{ 0U, 0U }, true);

  static vec2u ringPosition = { (GameEngine::BUFFER_WIDTH - m_ringSprite.dimensions.x) / 2,
    (GameEngine::BUFFER_HEIGHT - m_ringSprite.dimensions.y) / 2 };
  entities.emplace_back(m_ringSprite, ringPosition, false);

  vec2u sprite1_offset = m_player1.currentSprite().dimensions / 2U;
  vec2u sprite2_offset = m_player2.currentSprite().dimensions / 2U;

  entities.emplace_back(m_player1.currentSprite(), static_cast<vec2u>(m_player1.position) - sprite1_offset, false);
  entities.emplace_back(m_player2.currentSprite(), static_cast<vec2u>(m_player2.position) - sprite2_offset, false);

  // terrible hack for z-ordering
  if (m_player1.position.y > m_player2.position.y) {
    std::swap(entities[entities.size() - 2], entities[entities.size() - 1]);
  }

  if (m_in_minigame) { entities.emplace_back(m_minigame.sprite(), vec2u{ 0U, 0U }, false); }

  return entities;
}

void RingScene::updatePlayers(const float tick)
{
  static constexpr float ring_radius = 0.5F * Sprites::ring.dimensions.x;
  static constexpr auto screen_center =
    static_cast<vec2f>(vec2u{ GameEngine::BUFFER_WIDTH / 2, GameEngine::BUFFER_HEIGHT / 2 });

  if (m_rounds == max_rounds) { return; }

  if (distance(m_player1.position, screen_center) > ring_radius) {
    results.at(m_rounds) = Result::Loss;
  } else if (distance(m_player2.position, screen_center) > ring_radius) {
    results.at(m_rounds) = Result::Win;
  }

  const vec2f direction = setFacingDirections(m_player1, m_player2);
  m_player2.velocity = -1.0F * m_player2.speed * normalize(direction);

  m_player1.updateAnimation();
  m_player2.updateAnimation();

  std::string tmp_result{};
  switch (results.at(m_rounds)) {
  case Result::Win:
    tmp_result = "WIN! ";
    reset();
    break;
  case Result::Loss:
    tmp_result = "LOSE! ";
    reset();
    break;
  case Result::None:
    break;
  }

  m_debug_info.clear();
  m_debug_info.push_back(fmt::format(
    "{} {} {}", tmp_result, distance(m_player1.position, screen_center), distance(m_player2.position, screen_center)));

  auto playersWillCollide = [this](float increment) {
    auto p1_test_collider = m_player1.collider;
    auto p2_test_collider = m_player2.collider;

    p1_test_collider.position = m_player1.position + increment * m_player1.velocity;
    p2_test_collider.position = m_player2.position + increment * m_player2.velocity;

    return p1_test_collider.collision(p2_test_collider);
  };

  static constexpr milliseconds minigame_timeout{ 100.0 };
  if (!playersWillCollide(tick)) {
    m_players_state = PlayerState::Free;
  } else if (std::chrono::duration_cast<milliseconds>(std::chrono::steady_clock::now() - m_last_minigame_end).count()
             > minigame_timeout.count()) {
    m_debug_info.emplace_back("Players locked!");
    m_players_state = PlayerState::Locked;
    m_player1.velocity = { 0, 0 };
    m_player2.velocity = { 0, 0 };
    startMinigame();
  }

  m_player1.updatePosition(tick);
  m_player2.updatePosition(tick);

  m_debug_info.push_back(fmt::format("P1 velocity: ({} {})", m_player1.velocity.x, m_player1.velocity.y));
  m_debug_info.push_back(fmt::format("P2 velocity: ({} {})", m_player2.velocity.x, m_player2.velocity.y));
}

void RingScene::startMinigame()
{
  m_in_minigame = true;
  m_minigame.reset();
}


void RingScene::updateMinigame(const float tick)
{
  m_minigame.updateAnimation(tick);
  if (auto const res = m_minigame.result(); res.has_value()) {
    m_debug_info.emplace_back("Minigame result: {}", res.value());
    if (res.value()) {
      playerPushBack(m_player1, m_player2, PushBackStyle::Impulse);
    } else {
      playerPushBack(m_player2, m_player1, PushBackStyle::Impulse);
    }
    m_last_minigame_end = std::chrono::steady_clock::now();
    m_in_minigame = false;
  }
}

void RingScene::reset(bool erase_rounds)
{
  m_player1.position = p1_starting_pos;
  m_player2.position = p2_starting_pos;

  m_player1.velocity = vec2f{ 0.0F, 0.0F };
  m_player2.velocity = vec2f{ 0.0F, 0.0F };

  m_player1.stopPushBack();
  m_player2.stopPushBack();

  if (erase_rounds) {
    std::fill(begin(results), end(results), Result::None);
    m_rounds = 0U;
  } else {
    ++m_rounds;
  }
}

std::optional<bool> RingScene::finalResult() const
{
  auto wins = std::count(begin(results), end(results), Result::Win);
  auto losses = std::count(begin(results), end(results), Result::Loss);

  if (wins > (max_rounds / 2U)) {
    return true;
  } else if (losses > (max_rounds / 2U)) {
    return false;
  }

  return {};
}


vec2f RingScene::setFacingDirections(PlayableCharacter &p1, PlayableCharacter &p2)
{
  vec2f direction = p2.position - p1.position;

  // FIXME: this is kida ugly. But optimization day will always be tomorrow
  if (std::fabs(direction.x) > std::fabs(direction.y)) {
    // left or right
    if (direction.x > 0.0F) {
      p1.facing_direction = PlayerFacingDirection::Right;
      p2.facing_direction = PlayerFacingDirection::Left;
    } else {
      p1.facing_direction = PlayerFacingDirection::Left;
      p2.facing_direction = PlayerFacingDirection::Right;
    }
  } else {
    // remember: y > 0 points downwards in screen space!!!
    if (direction.y < 0.0F) {
      p1.facing_direction = PlayerFacingDirection::Up;
      p2.facing_direction = PlayerFacingDirection::Down;
    } else {
      p1.facing_direction = PlayerFacingDirection::Down;
      p2.facing_direction = PlayerFacingDirection::Up;
    }
  }

  return direction;
}

void RingScene::playerPushBack(PlayableCharacter &pushing_player, PlayableCharacter &pushed_player, PushBackStyle style)
{
  vec2f direction = pushed_player.position - pushing_player.position;

  static constexpr float pushback_velocity = 45.0F;
  static constexpr float constant_push_speed = 5.0F;

  switch (style) {
  case PushBackStyle::Impulse:
    pushed_player.beginPushBack(pushback_velocity * normalize(direction));
    break;
  case PushBackStyle::Constant:
    pushing_player.velocity = pushed_player.velocity = constant_push_speed * normalize(direction);
    break;
  }
}


}// namespace Sumo::Game