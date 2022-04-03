#include "ecs/components/sprite_component.hpp"

namespace Sumo::Ecs::Components {

void SpriteComponent::Draw(Bitmap &screenBuffer, vec2u position) const
{
  auto x_max = static_cast<unsigned int>(screenBuffer.width());
  auto y_max = static_cast<unsigned int>(screenBuffer.height());

  // if tiled we draw on the whole screen
  if (m_tiled) {
    position = { 0U, 0U };
  } else {
    x_max = std::min(position.x + m_sprite.dimX, static_cast<unsigned int>(screenBuffer.width()));
    y_max = std::min(position.y + m_sprite.dimY, static_cast<unsigned int>(screenBuffer.height()));
  }

  for (unsigned int iy = position.y; iy < y_max; ++iy) {
    for (unsigned int ix = position.x; ix < x_max; ++ix) {
      size_t spriteX = (ix - position.x) % m_sprite.dimX;
      size_t spriteY = (iy - position.y) % m_sprite.dimY;
      size_t spriteIdx = spriteY * m_sprite.dimX + spriteX;
      screenBuffer.at(ix, iy) = m_sprite.data[spriteIdx];
    }
  }
}

}// namespace Sumo::Ecs::Components