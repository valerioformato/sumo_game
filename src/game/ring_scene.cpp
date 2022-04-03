#include "game/ring_scene.hpp"

#include "game/assets/sprites/sand_tile.hpp"

namespace Sumo::Game {
RingScene::RingScene(std::shared_ptr<EntityManager> entManager) : GameScene(std::move(entManager))
{
  auto &ground_entity = entities.emplace_back(entityManager->add("ground"));
  entityManager->add_component(ground_entity, Ecs::Components::BackgroundSpriteComponent(Sumo::Sprites::sand_tile));
}
}// namespace Sumo::Game