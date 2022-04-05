#ifndef SUMO_ENGINE_HPP
#define SUMO_ENGINE_HPP

// c++ headers
#include <thread>

// dependencies headers
#include <ftxui/component/screen_interactive.hpp>// for ScreenInteractive

// project headers
#include "engine/renderer.hpp"
#include "engine/scene.hpp"
#include "game/ring_scene.hpp"

namespace Sumo {
class GameEngine
{
public:
  static constexpr unsigned int BUFFER_WIDTH = 180;
  static constexpr unsigned int BUFFER_HEIGHT = 100;

  GameEngine();
  ~GameEngine();

  void run();

  GameEngine(const GameEngine &) = delete;

private:
  std::unique_ptr<GameScene> m_scene = std::make_unique<Game::RingScene>();

  Renderer m_renderer{ BUFFER_WIDTH, BUFFER_HEIGHT };

  ftxui::Component m_mainComponent;
  ftxui::ScreenInteractive m_screen{ ftxui::ScreenInteractive::Fullscreen() };

  void DrawLoop();
  void Tick();

  std::atomic<bool> m_stopGameLoop;
  std::thread m_drawThread{ &GameEngine::DrawLoop, this };
  std::thread m_gameThread{ &GameEngine::Tick, this };
};
}// namespace Sumo

#endif