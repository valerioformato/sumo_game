#include <algorithm>

#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "utils/clock.hpp"
#include "utils/vec2.hpp"

namespace Sumo {

void Renderer::begin(const Color &clearColor)
{
  std::fill(m_frameBuffer->data().begin(), m_frameBuffer->data().end(), clearColor);
}

void Renderer::submit(const Sprite &sprite, vec2u screenPos)
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

ftxui::Element Renderer::end() { return ftxui::hbox({ m_bufferElement, m_debugElement }); }


}// namespace Sumo
