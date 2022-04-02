#include "engine/renderer.hpp"


namespace Sumo {

ftxui::Element Renderer::DrawScene()
{
  static auto lastFrameTime = std::chrono::steady_clock::now();

  // This code actually processes the draw event

  // TODO: draw all the entities in the current scene

  const auto drawEnd = std::chrono::steady_clock::now();

  // now actually draw the game elements
  auto result = ftxui::hbox({ ftxui::vbox({ m_screenBuffer | ftxui::border, ftxui::text("") | ftxui::flex }),
    ftxui::vbox({ ftxui::text("Frame: " + std::to_string(m_frameCounter)),
      ftxui::text(fmt::format(
        "Draw time: {}", std::chrono::duration_cast<std::chrono::milliseconds>(drawEnd - lastFrameTime))) }) });

  ++m_frameCounter;
  lastFrameTime = drawEnd;

  return result;
};

}// namespace Sumo