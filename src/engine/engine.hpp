#ifndef SUMO_ENGINE_HPP
#define SUMO_ENGINE_HPP

// c++ headers
#include <thread>

// dependencies headers
#include <ftxui/component/screen_interactive.hpp>// for ScreenInteractive

// project headers
#include "engine/main_menu.hpp"
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

  enum class GameState { MainMenu = 0, Playing, End };
  int m_state{ static_cast<int>(GameState::MainMenu) };

  MainMenu m_main_menu;
  Renderer m_renderer{ BUFFER_WIDTH, BUFFER_HEIGHT };

  ftxui::Component m_main_component;
  ftxui::Component m_main_menu_component;
  ftxui::Component m_game_component;
  ftxui::ScreenInteractive m_screen{ ftxui::ScreenInteractive::Fullscreen() };

  void startGame();

  void drawLoop();
  void tick();

  std::atomic<bool> m_stop_game_loop;
  std::thread m_draw_thread;
  std::thread m_game_thread;
};
}// namespace Sumo

#endif