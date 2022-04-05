#include <algorithm>

#include <fmt/format.h>

#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "utils/clock.hpp"
#include "utils/vec2.hpp"

namespace Sumo {

void Renderer::begin(const Color &clearColor)
{
  std::fill(m_frameBuffer->data().begin(), m_frameBuffer->data().end(), clearColor);
}

void Renderer::draw_sprite_at(Sprite sprite, vec2u screenPos)
{
  const auto &[tlx, tly] = screenPos;
  const auto &[brx, bry] = screenPos + sprite.dimensions;
  for (auto y = tly; y < bry; ++y) {
    for (auto x = tlx; x < brx; ++x) {
      if (in_range(x, 0U, m_frameBuffer->width()) && in_range(y, 0U, m_frameBuffer->height())) {
        m_frameBuffer->at(x, y) = sprite.at({ x - tlx, y - tly });
      }
    }
  }
}


void Renderer::submit(Sprite sprite, vec2u screenPos, bool tiled)
{
  if (!tiled) {
    draw_sprite_at(sprite, screenPos);
  } else {
    screenPos = { 0U, 0U };
    for (unsigned int iy = 0U; iy < (m_frameBuffer->height() / sprite.dimensions.y + 1); ++iy) {
      for (unsigned int ix = 0U; ix < (m_frameBuffer->width() / sprite.dimensions.x + 1); ++ix) {
        draw_sprite_at(sprite, screenPos);
        screenPos.x += sprite.dimensions.x;
      }
      screenPos.x = 0;
      screenPos.y += sprite.dimensions.y;
    }
  }
}

ftxui::Element Renderer::end() { return ftxui::hbox({ m_bufferElement, m_debugElement }); }


}// namespace Sumo
