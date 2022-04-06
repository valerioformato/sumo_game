#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "game/assets/sprites/blu.hpp"
#include "game/ring_scene.hpp"

namespace Sumo::Game {

RingScene::RingScene()
{
  m_player1 = PlayableCharacter{ Sprites::blu.frame(0) };
  m_player1Controller = PlayerController{ .event_handler = ftxui::CatchEvent([this](const ftxui::Event &event) {
    bool handled = true;
    vec2f velocity{ 0, 0 };

    if (event == ftxui::Event::ArrowUp) {
      velocity += { 0, -1 };
    } else if (event == ftxui::Event::ArrowDown) {
      velocity += { 0, 1 };
    } else if (event == ftxui::Event::ArrowLeft) {
      velocity += { -1, 0 };
    } else if (event == ftxui::Event::ArrowRight) {
      velocity += { 1, 0 };
    } else {
      handled = false;
    }

    m_player1.velocity = velocity;

    return handled;
  }) };
}

void RingScene::update(const milliseconds dt)
{
  static constexpr float millisecondsToSeconds = 0.001F;
  static constexpr float pSpeed = 3.0F;

  using namespace std::chrono_literals;
  static constexpr milliseconds player_animation_frametime = 500.0ms;

  static Clock player1_animation_timer;
  if (player1_animation_timer.elapsedTime().count() > player_animation_frametime.count()) {
    m_player1.sprite = Sprites::blu.frame(++m_player1.animation_frame % Sprites::blu.frames);
    player1_animation_timer.restart();
  }

  const auto tick = millisecondsToSeconds * static_cast<float>(dt.count());

  last_tick = tick;

  m_player1.position += pSpeed * tick * m_player1.velocity;
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