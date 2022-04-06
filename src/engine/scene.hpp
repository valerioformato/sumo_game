#ifndef SUMO_SCENE_HPP
#define SUMO_SCENE_HPP

// c++ headers
#include <chrono>

// project headers
#include "engine/sprite.hpp"
#include "utils/bitmap.hpp"
#include "utils/clock.hpp"

namespace Sumo {

class GameScene
{
public:
  GameScene() = default;
  virtual ~GameScene() = default;

  virtual void update(milliseconds dt) = 0;

  using DrawableEntity = std::tuple<Sprite, vec2u, bool>;
  virtual std::vector<DrawableEntity> drawableEntities() = 0;
};

}// namespace Sumo

#endif