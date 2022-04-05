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
    : m_frameBuffer(std::make_shared<Bitmap>(width, height)){

      };

  void begin(const Color &clearColor = Color{});

  void submit(const Sprite &sprite, vec2u screenPos);

  ftxui::Element end();

private:
  std::shared_ptr<Bitmap> m_frameBuffer;

  ftxui::Element m_bufferElement{ ftxui::vbox({ m_frameBuffer | ftxui::border, ftxui::text("") | ftxui::flex }) };
  ftxui::Element m_debugElement{ ftxui::vbox({ ftxui::text("") }) };
};

}// namespace Sumo

#endif