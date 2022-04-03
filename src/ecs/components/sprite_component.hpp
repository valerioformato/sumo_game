#ifndef SUMO_SPRITECOMPONENT_HPP
#define SUMO_SPRITECOMPONENT_HPP

// c++ headers
#include <memory>

// project headers
#include "engine/sprite.hpp"
#include "utils/bitmap.hpp"
#include "utils/vec2.hpp"

namespace Sumo::Ecs::Components {
class SpriteComponent
{
public:
  SpriteComponent(Sprite sprite, bool tiled) : m_sprite{ std::move(sprite) }, m_tiled{ tiled } {};

  // Draw the sprite placing the 0,0 corner at given position
  void Draw(Bitmap &screenBuffer, vec2u position) const;

private:
  void DrawTiled(Bitmap &screenBuffer) const;
  void DrawOnce(Bitmap &screenBuffer, vec2u position) const;

  Sprite m_sprite;
  bool m_tiled;
};

}// namespace Sumo::Ecs::Components
#endif