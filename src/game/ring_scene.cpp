#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "game/assets/sprites/sand_tile.hpp"
#include "game/ring_scene.hpp"

namespace Sumo::Game {
RingScene::RingScene(std::shared_ptr<EntityManager> entManager) : GameScene(std::move(entManager))
{
  auto &ground_entity = entities.emplace_back(entityManager->add("ground"));
  entityManager->add_component(ground_entity, Ecs::Components::BackgroundSpriteComponent(Sumo::Sprites::sand_tile));

  // test sprite: one white square :)
  // TODO: replace with real sprite
  player1 = PlayableCharacter{ Sprite{ 1U, 1U, std::array{ Color{ 255, 255, 255 } } } };// NOLINT magic numbers
  player1Controller = PlayerController{ .eventHandler = ftxui::CatchEvent([this](const ftxui::Event &event) {
    if (event == ftxui::Event::ArrowUp) { player1.velocity = { 0, 1 }; }
    if (event == ftxui::Event::ArrowDown) { player1.velocity = { 0, -1 }; }
    if (event == ftxui::Event::ArrowLeft) { player1.velocity = { -1, 0 }; }
    if (event == ftxui::Event::ArrowRight) { player1.velocity = { 1, 0 }; }

    return true;
  }) };
}
}// namespace Sumo::Game