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
  ftxui::Component ftxRenderer{ ftxui::Renderer([this] { return this->DrawScene(); }) };

  // FIXME: If we declare DrawScene as private then we trigger a false positive in cppcheck "unusedPrivateFunction"
  // check. Even if it is clearly used in the lambda above
  ftxui::Element DrawScene()
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

private:
  std::shared_ptr<Bitmap> m_screenBuffer;

  unsigned long long m_frameCounter{ 0 };
};
}// namespace Sumo

#endif