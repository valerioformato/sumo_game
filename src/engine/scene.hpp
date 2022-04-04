#ifndef SUMO_SCENE_HPP
#define SUMO_SCENE_HPP

// c++ headers
#include <chrono>

// project headers
#include "utils/bitmap.hpp"

#include "ecs/components.hpp"
#include "ecs/entity.hpp"

namespace Sumo {
class GameScene
{
public:
  GameScene() = default;
  explicit GameScene(std::shared_ptr<EntityManager> entMgr) : entityManager{ entMgr } {}
  virtual ~GameScene() = default;

  virtual void Update(std::chrono::milliseconds dt) = 0;

  std::vector<Ecs::Entity> entities;
  std::shared_ptr<EntityManager> entityManager;
};
}// namespace Sumo

#endif