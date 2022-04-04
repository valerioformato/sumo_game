#include "engine/engine.hpp"

namespace Sumo {

GameEngine::GameEngine()
{
  m_renderer.currentScene = m_scene;
  m_screen.Loop(m_renderer.ftxRenderer);
};

GameEngine::~GameEngine()
{
  m_stopGameLoop = true;
  m_gameThread.join();
}

void GameEngine::GameLoop()
{
  while (!m_stopGameLoop) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1.0s / 60.0);// NOLINT magic numbers
    m_screen.PostEvent(ftxui::Event::Custom);
  }
};
}// namespace Sumo