#include <algorithm>

#include "engine/renderer.hpp"
#include "engine/engine.hpp"
#include "utils/vec2.hpp"
#include "utils/clock.hpp"


namespace Sumo {

void Renderer::begin(const Color& clearColor)
{
  std::fill(m_frameBuffer->data().begin(), m_frameBuffer->data().end(), clearColor); 
}

void Renderer::submit(const Sprite& sprite)
{
  const auto& [tlx, tly] = sprite.m_topLeft; 
  const auto& [brx, bry] = sprite.m_bottomRight; 
  for(auto y = tly; y < bry; ++y)
    for(auto x = tlx; x < brx; ++x)
    {
      if(in_range(x, 0, m_frameBuffer->width()) && in_range(y, 0, m_frameBuffer->height()))
        m_frameBuffer->at(x, y) = sprite.m_tex->at(x - tlx, y - tly); 
    }
}

ftxui::Element Renderer::end()
{
  return m_frameBuffer; 
}


}// namespace Sumo