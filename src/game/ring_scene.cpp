#include <fmt/chrono.h>
#include <fmt/format.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "game/assets/sprites/blu.hpp"
#include "game/ring_scene.hpp"

namespace Sumo::Game {

bool isKeyArrowEvent(const ftxui::Event &event)
{
  return (event == ftxui::Event::ArrowLeft || event == ftxui::Event::ArrowRight || event == ftxui::Event::ArrowUp
          || event == ftxui::Event::ArrowDown);
}

RingScene::RingScene()
{
  m_player1 = PlayableCharacter{ Sprites::blu.frame(0) };
  m_player1.position = vec2f{ 80.0F, 40.0F };// NOLINT magic numbers
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

    m_debug_info = fmt::format("{} {}ms ago", isKeyArrowEvent(event) ? "key" : "custom", dt.count());

    return handled;
  });
}

void RingScene::update(const milliseconds dt)
{
  static constexpr float milliseconds_to_seconds = 0.001F;

  using namespace std::chrono_literals;
  static constexpr milliseconds player_animation_frametime = 500.0ms;

  static Clock player1_animation_timer;
  if (player1_animation_timer.elapsedTime().count() > player_animation_frametime.count()) {
    m_player1.sprite = Sprites::blu.frame(++m_player1.animation_frame % Sprites::blu.frames);
    player1_animation_timer.restart();
  }

  const auto tick = milliseconds_to_seconds * static_cast<float>(dt.count());

  m_player1.position += tick * m_player1.velocity;
}

std::vector<GameScene::DrawableEntity> RingScene::drawableEntities()
{
  std::vector<GameScene::DrawableEntity> entities;

  entities.emplace_back(std::make_tuple(m_groundSprite, vec2u{ 0U, 0U }, true));

  auto pos = static_cast<vec2u>(m_player1.position);
  entities.emplace_back(std::make_tuple(m_player1.sprite, pos, false));

  return entities;
}


}// namespace Sumo::Game