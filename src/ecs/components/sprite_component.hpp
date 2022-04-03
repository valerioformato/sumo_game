#ifndef SUMO_SPRITECOMPONENT_HPP
#define SUMO_SPRITECOMPONENT_HPP

// c++ headers
#include <memory>

// project headers
#include "engine/sprite.hpp"
#include "utils/bitmap.hpp"

namespace Sumo::Ecs::Components {
class SpriteComponent
{
public:
  SpriteComponent(Sprite sprite, bool tiled) : m_sprite{ std::move(sprite) }, m_tiled{ tiled } {};

  void Draw(Bitmap &screenBuffer);

private:
  Sprite m_sprite;
  bool m_tiled;
};

}// namespace Sumo::Ecs::Components
#endif