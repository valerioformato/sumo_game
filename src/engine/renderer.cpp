#include <algorithm>

#include <fmt/format.h>

#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "utils/clock.hpp"
#include "utils/color.hpp"
#include "utils/math.hpp"
#include "utils/vec2.hpp"

namespace Sumo {

Renderer::Renderer(std::size_t width, std::size_t height) : m_frame_buffer(std::make_shared<Bitmap>(width, height))
{
  for (auto &state : round_states) { m_ui_component->Add(ftxui::Checkbox("", &state)); }
}

void Renderer::begin(const ColorI32 &clear_color)
{
  std::fill(m_frame_buffer->data().begin(), m_frame_buffer->data().end(), clear_color);
}

void Renderer::drawSpriteAt(const StaticSprite sprite, vec2u screen_pos)
{
  const auto &[tlx, tly] = screen_pos;
  const auto &[brx, bry] = screen_pos + sprite.dimensions;
  for (auto y = tly; y < bry; ++y) {
    for (auto x = tlx; x < brx; ++x) {
      if (in_range(x, 0U, m_frame_buffer->width()) && in_range(y, 0U, m_frame_buffer->height())) {
        m_frame_buffer->at(x, y) = alphaBlend(sprite.at({ x - tlx, y - tly }), m_frame_buffer->at(x, y));
      }
    }
  }
}


void Renderer::submit(const StaticSprite sprite, vec2u screen_pos, const bool tiled)
{
  if (!tiled) {
    drawSpriteAt(sprite, screen_pos);
  } else {
    screen_pos = { 0U, 0U };
    for (unsigned int iy = 0U; iy < (m_frame_buffer->height() / sprite.dimensions.y + 1); ++iy) {
      for (unsigned int ix = 0U; ix < (m_frame_buffer->width() / sprite.dimensions.x + 1); ++ix) {
        drawSpriteAt(sprite, screen_pos);
        screen_pos.x += sprite.dimensions.x;
      }
      screen_pos.x = 0;
      screen_pos.y += sprite.dimensions.y;
    }
  }
}

ftxui::Element Renderer::end()
{
  return ftxui::hbox({ m_buffer_element, ftxui::vbox({ checkboxes(), m_debug_element }) });
}


}// namespace Sumo
