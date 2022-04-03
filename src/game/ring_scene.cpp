#include "game/ring_scene.hpp"

#include "game/assets/sprites/sand_tile.hpp"

namespace Sumo::Game {
RingScene::RingScene(EntityManager &entityManager)
{
  auto &ground_entity = entities.emplace_back(entityManager.add("ground"));
  entityManager.add_component(ground_entity, Ecs::Components::SpriteComponent(Sumo::Sprites::sand_tile, true));
}
}// namespace Sumo::Game