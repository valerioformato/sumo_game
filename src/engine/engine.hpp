#ifndef SUMO_ENGINE_HPP
#define SUMO_ENGINE_HPP

// c++ headers
#include <thread>

// dependencies headers
#include <ftxui/component/screen_interactive.hpp>// for ScreenInteractive

// project headers
#include "engine/renderer.hpp"
#include "engine/scene.hpp"

namespace Sumo {
class GameEngine
{
public:
  static constexpr unsigned int BUFFER_WIDTH = 180;
  static constexpr unsigned int BUFFER_HEIGHT = 100;

  GameEngine();
  ~GameEngine();

  void run(); 

  void rendererSubmit(const Sprite& sprite)
  {
    m_renderer.submit(sprite); 
  }

  GameEngine(const GameEngine &) = delete;

private:
  std::unique_ptr<GameScene> m_scene; 

  Renderer m_renderer{ BUFFER_WIDTH, BUFFER_HEIGHT };

  ftxui::ScreenInteractive m_screen{ ftxui::ScreenInteractive::Fullscreen() };

  void Tick();

  std::atomic<bool> m_stopGameLoop;
  std::thread m_gameThread{ &GameEngine::Tick, this };
};
}// namespace Sumo

#endif