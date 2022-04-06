#ifndef SUMO_RENDERER_HPP
#define SUMO_RENDERER_HPP

// dependencies headers
#include <ftxui/component/component.hpp>// for ScreenInteractive

// project headers
#include "engine/sprite.hpp"
#include "utils/bitmap.hpp"
#include "utils/vec2.hpp"

namespace Sumo {

class Renderer
{
public:
  Renderer(std::size_t width, std::size_t height)
    : m_frame_buffer(std::make_shared<Bitmap>(width, height)){

      };

  void begin(const Color &clearColor = Color{});

  void submit(Sprite sprite, vec2u screen_pos, bool tiled = false);

  ftxui::Element end();

  void display_debug_text(std::string text) { m_debug_element = ftxui::vbox({ m_debug_element, ftxui::text(text) }); }
  void reset_debug_text() { m_debug_element = ftxui::vbox({}); };

private:
  std::shared_ptr<Bitmap> m_frame_buffer;

  ftxui::Element m_buffer_element{ ftxui::vbox({ m_frame_buffer | ftxui::border, ftxui::text("") | ftxui::flex }) };
  ftxui::Element m_debug_element{ ftxui::vbox({}) };

  void drawSpriteAt(Sprite sprite, vec2u screen_pos);
};

}// namespace Sumo

#endif