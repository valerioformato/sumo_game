#include "ecs/components/background_sprite_component.hpp"

namespace Sumo::Ecs::Components {
void BackgroundSpriteComponent::Draw(Bitmap &screenBuffer) const
{
  static std::vector<Color> background(screenBuffer.width() * screenBuffer.height());

  // credit to @the_whole_daisy for this amazing trick
  // https://twitter.com/The_Whole_Daisy/status/1306316395064496128?s=20&t=S9shvBJ-tDN2VTJZexJ1UQ
  [[maybe_unused]] static bool unused = [&]() {
    vec2u position{ 0, 0 };
    while (position.y < screenBuffer.height()) {
      while (position.x < screenBuffer.width()) {
        auto x_max = std::min(m_sprite.dimX, static_cast<unsigned int>(screenBuffer.width()) - position.x);
        auto y_max = std::min(m_sprite.dimY, static_cast<unsigned int>(screenBuffer.height()) - position.y);

        for (unsigned int iy = 0; iy < y_max; ++iy) {
          for (unsigned int ix = 0; ix < x_max; ++ix) {
            size_t spriteIdx = ix * m_sprite.dimX + iy;
            size_t bufferIdx = (iy + position.y) * screenBuffer.width() + ix + position.x;
            background[bufferIdx] = m_sprite.data[spriteIdx];
          }
        }
        position.x += m_sprite.dimX;
      }
      position.y += m_sprite.dimY;
      position.x = 0;
    }
    return true;
  }();

  std::copy(begin(background), end(background), begin(screenBuffer.data()));
}

}// namespace Sumo::Ecs::Components