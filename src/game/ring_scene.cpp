#include <fmt/chrono.h>
#include <fmt/format.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "game/ring_scene.hpp"

namespace Sumo::Game {

bool isKeyArrowEvent(const ftxui::Event &event)
{
  return (event == ftxui::Event::ArrowLeft || event == ftxui::Event::ArrowRight || event == ftxui::Event::ArrowUp
          || event == ftxui::Event::ArrowDown);
}

RingScene::RingScene()
{
  m_player1.position = vec2f{ 120.0F, 40.0F };// NOLINT magic numbers
  m_player2.position = vec2f{ 60.0F, 30.0F };// NOLINT magic numbers


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

  setFacingDirections(m_player1, m_player2);

  m_player1.updateAnimation();
  m_player2.updateAnimation();

  m_debug_info = fmt::format("p1 facing {}, p2 facing {}",
    direction_debug_name[m_player1.facing_direction],
    direction_debug_name[m_player2.facing_direction]);

  const auto tick = milliseconds_to_seconds * static_cast<float>(dt.count());

  m_player1.position += tick * m_player1.velocity;
}

std::vector<GameScene::DrawableEntity> RingScene::drawableEntities()
{
  std::vector<GameScene::DrawableEntity> entities;

  entities.emplace_back(std::make_tuple(m_groundSprite, vec2u{ 0U, 0U }, true));

  entities.emplace_back(std::make_tuple(m_player1.currentSprite(), static_cast<vec2u>(m_player1.position), false));
  entities.emplace_back(std::make_tuple(m_player2.currentSprite(), static_cast<vec2u>(m_player2.position), false));

  return entities;
}


void RingScene::setFacingDirections(PlayableCharacter &p1, PlayableCharacter &p2)
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
}


}// namespace Sumo::Game