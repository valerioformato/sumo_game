#ifndef SUMO_RENDERER_HPP
#define SUMO_RENDERER_HPP

// dependencies headers
#include <ftxui/component/component.hpp>

// project headers
#include "engine/sprite.hpp"
#include "utils/bitmap.hpp"
#include "utils/vec2.hpp"

namespace Sumo {

class Renderer
{
public:
  Renderer(std::size_t width, std::size_t height);

  void begin(const ColorI32 &clear_color = ColorI32{});

  void submit(StaticSprite sprite, vec2u screen_pos, bool tiled = false);

  ftxui::Element end();

  [[nodiscard]] auto lock_buffer() { return m_frame_buffer->lock(); }

  void display_debug_text(const std::string &text)
  {
    m_debug_element = ftxui::vbox({ m_debug_element, ftxui::text(text) });
  }

  void reset_debug_text() { m_debug_element = ftxui::vbox({}); };

  std::array<bool, 3> round_states{ false, false, false };

  ftxui::Element checkboxes() const
  {
    return ftxui::vbox({ ftxui::text("Rounds:"), m_ui_component->Render() | ftxui::center | ftxui::border });
  };

private:
  std::shared_ptr<Bitmap> m_frame_buffer;

  ftxui::Element m_buffer_element{ ftxui::vbox({ m_frame_buffer | ftxui::border, ftxui::text("") | ftxui::flex }) };
  ftxui::Element m_debug_element{ ftxui::vbox({}) };

  ftxui::Component m_ui_component{ ftxui::Container::Horizontal({}) };


  void drawSpriteAt(StaticSprite sprite, vec2u screen_pos);
};

}// namespace Sumo

#endif