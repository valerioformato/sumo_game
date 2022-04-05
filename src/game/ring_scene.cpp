#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "game/assets/sprites/sand_tile.hpp"
#include "game/ring_scene.hpp"

namespace Sumo::Game {

constexpr std::array tempPlayerSprite{ Color{ 255, 255, 255 } };// NOLINT magic numbers

RingScene::RingScene(std::shared_ptr<EntityManager> entManager) : GameScene(std::move(entManager))
{
  auto &ground_entity = entities.emplace_back(entityManager->add("ground"));
  entityManager->add_component(ground_entity, Ecs::Components::BackgroundSpriteComponent(Sumo::Sprites::sand_tile));

  // test sprite: one white square :)
  // TODO: replace with real sprite
  player1 = PlayableCharacter{ Sprite{ 1U, 1U, tempPlayerSprite } };
  player1Controller = PlayerController{ .eventHandler = ftxui::CatchEvent([this](const ftxui::Event &event) {
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

    player1.velocity = velocity;

    return handled;
  }) };
}

void RingScene::Update(milliseconds dt)
{
  static constexpr float millisecondsToSeconds = 0.001F;
  static constexpr float pSpeed = 3.0F;

  auto tick = millisecondsToSeconds * static_cast<float>(dt.count());

  lastTick = tick;

  player1.position += pSpeed * tick * player1.velocity;
}
}// namespace Sumo::Game