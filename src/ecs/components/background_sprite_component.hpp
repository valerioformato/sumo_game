#ifndef SUMO_BACKGROUNDSPRITECOMPONENT_HPP
#define SUMO_BACKGROUNDSPRITECOMPONENT_HPP

// c++ headers
#include <memory>

// project headers
#include "engine/sprite.hpp"
#include "utils/bitmap.hpp"
#include "utils/vec2.hpp"

namespace Sumo::Ecs::Components {
class BackgroundSpriteComponent
{
public:
  explicit BackgroundSpriteComponent(Sprite sprite) : m_sprite{ std::move(sprite) } {};

  // Draw the sprite placing the 0,0 corner at given position
  void Draw(Bitmap &screenBuffer) const;

private:
  Sprite m_sprite;
};

}// namespace Sumo::Ecs::Components
#endif