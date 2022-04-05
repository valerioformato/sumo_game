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
  m_drawThread.join();
  m_gameThread.join();
}

using milliseconds = std::chrono::duration<double, std::milli>;

void GameEngine::DrawLoop()
{
  using namespace std::chrono_literals;
  static constexpr milliseconds targetFrameTime = 1.0s / 30.0;

  while (!m_stopGameLoop) {
    static auto lastDraw = std::chrono::steady_clock::now();

    m_renderer.DrawScene();

    auto drawTime = std::chrono::steady_clock::now();
    auto dt = std::chrono::duration_cast<milliseconds>(drawTime - lastDraw);

    if (dt.count() < targetFrameTime.count()) { std::this_thread::sleep_for(targetFrameTime - dt); }

    lastDraw = drawTime;
  }
}

void GameEngine::GameLoop()
{
  while (!m_stopGameLoop) {
    static auto lastTick = std::chrono::steady_clock::now();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1.0s / 30.0);// NOLINT magic numbers

    auto updateTime = std::chrono::steady_clock::now();

    auto dt = std::chrono::duration_cast<milliseconds>(updateTime - lastTick);
    m_scene->Update(dt);

    lastTick = updateTime;

    m_screen.PostEvent(ftxui::Event::Custom);
  }
};
}// namespace Sumo