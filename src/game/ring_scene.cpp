#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "game/assets/sprites/blu.hpp"
#include "game/ring_scene.hpp"

namespace Sumo::Game {

RingScene::RingScene()
{
  // test sprite: one white square :)
  // TODO: replace with real sprite
  m_player1 = PlayableCharacter{ Sprites::blu.frame(0) };
  m_player1Controller = PlayerController{ .eventHandler = ftxui::CatchEvent([this](const ftxui::Event &event) {
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

void RingScene::Update(milliseconds dt)
{
  static constexpr float millisecondsToSeconds = 0.001F;
  static constexpr float pSpeed = 3.0F;

  auto tick = millisecondsToSeconds * static_cast<float>(dt.count());

  lastTick = tick;

  m_player1.position += pSpeed * tick * m_player1.velocity;
}

std::vector<GameScene::DrawableEntity> RingScene::DrawableEntities()
{
  std::vector<GameScene::DrawableEntity> entities;

  entities.emplace_back(std::make_tuple(m_groundSprite, vec2u{ 0U, 0U }, true));

  vec2u pos{ static_cast<unsigned int>(m_player1.position.x), static_cast<unsigned int>(m_player1.position.y) };
  entities.emplace_back(std::make_tuple(m_player1.sprite, pos, false));

  return entities;
}


}// namespace Sumo::Game