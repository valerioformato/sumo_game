#include "engine/engine.hpp"

namespace Sumo {

GameEngine::GameEngine()
{
};

GameEngine::~GameEngine()
{
  m_stopGameLoop = true;
  m_gameThread.join();
}

void GameEngine::run()
{
  m_screen.Loop(ftxui::Renderer([&] {
    m_renderer.begin();

    m_scene->update(); 

    return m_renderer.end(); 
  })); 
}

void GameEngine::Tick()
{
  while (!m_stopGameLoop) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1.0s / 60.0);// NOLINT magic numbers
    m_screen.PostEvent(ftxui::Event::Custom);
  }
};
}// namespace Sumo