#ifndef SUMO_SCENE_HPP
#define SUMO_SCENE_HPP

// project headers
#include "utils/bitmap.hpp"

#include "ecs/entity.hpp"

namespace Sumo {
class GameScene
{
public:
  static constexpr Color sandColor{ 143, 112, 27 };

  std::vector<Ecs::Entity> entities;
};
}// namespace Sumo

#endif