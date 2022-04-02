#ifndef SUMO_ENGINE_HPP
#define SUMO_ENGINE_HPP

// c++ headers
#include <thread>

#include <ftxui/component/screen_interactive.hpp>// for ScreenInteractive

#include "engine/renderer.hpp"
#include "engine/scene.hpp"

namespace Sumo {
class GameEngine
{
public:
  static constexpr unsigned int BUFFER_WIDTH = 180;
  static constexpr unsigned int BUFFER_HEIGHT = 100;

  GameEngine() { m_screen.Loop(m_renderer.ftxRenderer); };

private:
  std::shared_ptr<GameScene> m_scene;

  Renderer m_renderer{ BUFFER_WIDTH, BUFFER_HEIGHT };

  // ftxui::ScreenInteractive m_screen{ ftxui::ScreenInteractive::FixedSize(BUFFER_WIDTH + 2, BUFFER_HEIGHT / 2 + 2) };
  ftxui::ScreenInteractive m_screen{ ftxui::ScreenInteractive::Fullscreen() };


  void Tick(std::stop_token stop_token)//
  {
    while (!stop_token.stop_requested()) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(1.0s / 30.0);// NOLINT magic numbers
      m_screen.PostEvent(ftxui::Event::Custom);
    }
  };

  std::jthread m_gameThread{ std::bind_front(&GameEngine::Tick, this) };
};
}// namespace Sumo

#endif