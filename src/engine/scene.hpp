#ifndef SUMO_SCENE_HPP
#define SUMO_SCENE_HPP

// c++ headers
#include <chrono>
#include <mutex>

// dependencies headers
#include <ftxui/component/component.hpp>

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

  using DrawableEntity = std::tuple<StaticSprite, vec2u, bool>;
  virtual std::vector<DrawableEntity> drawableEntities() = 0;

  virtual std::vector<ftxui::ComponentDecorator> eventHandlers() = 0;
};

}// namespace Sumo

#endif