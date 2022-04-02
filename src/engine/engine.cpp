#include "engine/engine.hpp"

namespace Sumo {

GameEngine::GameEngine() { m_screen.Loop(m_renderer.ftxRenderer); };

GameEngine::~GameEngine()
{
  m_stopGameLoop = true;
  m_gameThread.join();
}

void GameEngine::Tick()
{
  while (!m_stopGameLoop) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1.0s / 30.0);// NOLINT magic numbers
    m_screen.PostEvent(ftxui::Event::Custom);
  }
};
}// namespace Sumo