#include "engine/engine.hpp"

namespace Sumo {

GameEngine::GameEngine()
{
  m_renderer.currentScene = m_scene;

  // FIXME: ugly, but temporary
  auto scene = std::static_pointer_cast<Game::RingScene>(m_scene);
  m_mainComponent |= scene->player1Controller.eventHandler;

  m_screen.Loop(m_mainComponent);
};

GameEngine::~GameEngine()
{
  m_stopGameLoop = true;
  m_gameThread.join();
}

void GameEngine::GameLoop()
{

  while (!m_stopGameLoop) {
    static auto lastTick = std::chrono::steady_clock::now();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1.0s / 30.0);// NOLINT magic numbers

    auto updateTime = std::chrono::steady_clock::now();

    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(updateTime - lastTick);
    m_scene->Update(dt);

    lastTick = updateTime;

    // FIXME: all keyboard events cause also a re-draw, figure out a way around this?
    // m_screen.PostEvent(ftxui::Event::Custom);
  }
};
}// namespace Sumo