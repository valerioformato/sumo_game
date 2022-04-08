#include <fmt/chrono.h>
#include <fmt/format.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "engine/engine.hpp"
#include "game/ring_scene.hpp"

namespace Sumo::Game {

bool isKeyArrowEvent(const ftxui::Event &event)
{
  return (event == ftxui::Event::ArrowLeft || event == ftxui::Event::ArrowRight || event == ftxui::Event::ArrowUp
          || event == ftxui::Event::ArrowDown);
}

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
    bool handled = true;

    std::chrono::steady_clock::time_point event_time = std::chrono::steady_clock::now();

    auto dt = std::chrono::duration_cast<milliseconds>(event_time - m_player1_controller.last_event.key_time);

    if (isKeyArrowEvent(m_player1_controller.last_event.event) && !isKeyArrowEvent(event)) { return false; }

    if (!isKeyArrowEvent(m_player1_controller.last_event.event) && !isKeyArrowEvent(event)
        && dt.count() > keyboard_timeout.count()) {
      m_player1.velocity = { 0, 0 };
      handled = false;
    }

    m_player1_controller.last_event.key_event = event;

    if (event == ftxui::Event::ArrowUp) {
      m_player1_controller.last_event.key_event = event;
      m_player1_controller.last_event.key_time = event_time;
      m_player1.velocity = m_player1.speed * vec2f{ 0, -1 };
    } else if (event == ftxui::Event::ArrowDown) {
      m_player1_controller.last_event.key_event = event;
      m_player1_controller.last_event.key_time = event_time;
      m_player1.velocity = m_player1.speed * vec2f{ 0, 1 };
    } else if (event == ftxui::Event::ArrowLeft) {
      m_player1_controller.last_event.key_event = event;
      m_player1_controller.last_event.key_time = event_time;
      m_player1.velocity = m_player1.speed * vec2f{ -1, 0 };
    } else if (event == ftxui::Event::ArrowRight) {
      m_player1_controller.last_event.key_event = event;
      m_player1_controller.last_event.key_time = event_time;
      m_player1.velocity = m_player1.speed * vec2f{ 1, 0 };
    }

    // m_debug_info = fmt::format("{} {}ms ago", isKeyArrowEvent(event) ? "key" : "custom", dt.count());

    return handled;
  });
}

void RingScene::update(const milliseconds dt)
{
  static constexpr float milliseconds_to_seconds = 0.001F;
  static constexpr float ring_radius = 0.5F * Sprites::ring.dimensions.x;
  static constexpr auto screen_center =
    static_cast<vec2f>(vec2u{ GameEngine::BUFFER_WIDTH / 2, GameEngine::BUFFER_HEIGHT / 2 });

  if (distance(m_player1.position, screen_center) > ring_radius) {
    result = Result::Loss;
  } else if (distance(m_player2.position, screen_center) > ring_radius) {
    result = Result::Win;
  }

  vec2f direction = setFacingDirections(m_player1, m_player2);
  m_player2.velocity = -1.0F * m_player2.speed * normalize(direction);

  m_player1.updateAnimation();
  m_player2.updateAnimation();

  std::string tmp_result{};
  switch (result) {
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

  m_debug_info = fmt::format(
    "{} {} {}", tmp_result, distance(m_player1.position, screen_center), distance(m_player2.position, screen_center));

  const auto tick = milliseconds_to_seconds * static_cast<float>(dt.count());

  auto playersWillCollide = [this](float increment) {
    auto p1_test_collider = m_player1.collider;
    auto p2_test_collider = m_player2.collider;

    p1_test_collider.position = m_player1.position + increment * m_player1.velocity;
    p2_test_collider.position = m_player2.position + increment * m_player2.velocity;

    return p1_test_collider.collision(p2_test_collider);
  };

  if (!playersWillCollide(tick)) {
    m_player1.updatePosition(tick);
    m_player2.updatePosition(tick);
  } else {
    m_debug_info += " Collision!";
    m_player1.velocity = { 0, 0 };
    m_player2.velocity = { 0, 0 };
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

  return entities;
}

void RingScene::reset()
{
  m_player1.position = p1_starting_pos;
  m_player2.position = p2_starting_pos;

  m_player1.velocity = vec2f{ 0.0F, 0.0F };
  m_player2.velocity = vec2f{ 0.0F, 0.0F };

  result = Result::None;
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


}// namespace Sumo::Game