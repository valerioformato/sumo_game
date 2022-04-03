#include <stdexcept>

#include "ecs/components/sprite_component.hpp"

namespace Sumo::Ecs::Components {

void SpriteComponent::Draw(Bitmap &screenBuffer, vec2u position) const
{
  if (m_tiled) {
    while (position.y < screenBuffer.height()) {
      while (position.x < screenBuffer.width()) {
        DrawOnce(screenBuffer, position);
        position.x += m_sprite.dimX;
      }
      position.y += m_sprite.dimY;
      position.x = 0;
    }
  } else {
    DrawOnce(screenBuffer, position);
  }
}

void SpriteComponent::DrawOnce(Bitmap &screenBuffer, vec2u position) const
{
  auto x_max = std::min(m_sprite.dimX, static_cast<unsigned int>(screenBuffer.width()) - position.x);
  auto y_max = std::min(m_sprite.dimY, static_cast<unsigned int>(screenBuffer.height()) - position.y);

  for (unsigned int iy = 0; iy < y_max; ++iy) {
    for (unsigned int ix = 0; ix < x_max; ++ix) {
      size_t spriteIdx = ix * m_sprite.dimX + iy;
      screenBuffer.at(ix + position.x, iy + position.y) = m_sprite.data[spriteIdx];
    }
  }
}

}// namespace Sumo::Ecs::Components