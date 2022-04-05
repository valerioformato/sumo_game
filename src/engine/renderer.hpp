#ifndef SUMO_RENDERER_HPP
#define SUMO_RENDERER_HPP

// dependencies headers
#include <fmt/chrono.h>
#include <ftxui/component/component.hpp>// for ScreenInteractive

// project headers
#include "engine/scene.hpp"
#include "utils/bitmap.hpp"

namespace Sumo {
class Renderer
{
public:
  Renderer(unsigned int dimx, unsigned int dimy) : m_screenBuffer{ std::make_shared<Bitmap>(dimx, dimy) } {};

  std::shared_ptr<GameScene> currentScene;
  ftxui::Component ftxRenderer{ ftxui::Renderer([this] { return this->Render(); }) };

  void DrawScene();

private:
  std::mutex m_screenBufferMtx;
  std::shared_ptr<Bitmap> m_screenBuffer;

  ftxui::Element m_bufferElement{ ftxui::vbox({ m_screenBuffer | ftxui::border, ftxui::text("") | ftxui::flex }) };
  ftxui::Element m_debugElement{ ftxui::vbox({ ftxui::text("") }) };

  unsigned long long m_frameCounter{ 0 };

  ftxui::Element Render();
};
}// namespace Sumo

#endif