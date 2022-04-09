#include <fmt/chrono.h>
#include <fmt/format.h>

#include "engine/engine.hpp"

namespace Sumo {

GameEngine::GameEngine()
{
  m_renderer.begin();
  m_main_component = ftxui::Renderer([&] { return m_renderer.end(); });

  // FIXME: ugly, but temporary
  auto *scene = dynamic_cast<Game::RingScene *>(m_scene.get());
  m_main_component |= scene->eventHandler();
};

GameEngine::~GameEngine()
{
  m_stop_game_loop = true;
  m_draw_thread.join();
  m_game_thread.join();
}

using milliseconds = std::chrono::duration<double, std::milli>;

void GameEngine::drawLoop()
{
  using namespace std::chrono_literals;
  static constexpr milliseconds target_frame_time = 1.0s / 60.0;

  unsigned int frame_counter{ 0 };

  while (!m_stop_game_loop) {
    static auto last_frame = std::chrono::steady_clock::now();

    auto drawTime = std::chrono::steady_clock::now();
    auto dt = std::chrono::duration_cast<milliseconds>(drawTime - last_frame);
    last_frame = std::chrono::steady_clock::now();

    {
      auto g_lock = m_renderer.lock_buffer();
      for (auto [sprite, position, tiled] : m_scene->drawableEntities()) { m_renderer.submit(sprite, position, tiled); }
    }

    // NOTE: we have to use .count here because of this issue with msvc 19
    // see https://github.com/fmtlib/fmt/issues/2854
    static constexpr double milliseconds_to_seconds = 1000.0;
    // this happens too fast, let's slow it down by 5x
    if ((frame_counter % 5) == 0U) {// NOLINT magic numbers
      m_renderer.reset_debug_text();
      m_renderer.display_debug_text(std::to_string(frame_counter));
      m_renderer.display_debug_text(fmt::format(
        "{} fps, frame time = {:4.2f}ms", static_cast<unsigned int>(milliseconds_to_seconds / dt.count()), dt.count()));
      for (const auto &line : dynamic_cast<Game::RingScene *>(m_scene.get())->debugInfo()) {
        m_renderer.display_debug_text(line);
      }
    }
    auto draw_end_time = std::chrono::steady_clock::now();
    auto draw_duration = std::chrono::duration_cast<milliseconds>(draw_end_time - drawTime);

    ++frame_counter;

    if (draw_duration.count() < target_frame_time.count()) {
      std::this_thread::sleep_for(target_frame_time - draw_duration);
    }
  }
}

void GameEngine::run() { m_screen.Loop(m_main_component); }

void GameEngine::tick()
{
  while (!m_stop_game_loop) {
    static auto last_tick = std::chrono::steady_clock::now();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1.0s / 30.0);// NOLINT magic numbers

    auto update_time = std::chrono::steady_clock::now();

    const auto dt = std::chrono::duration_cast<milliseconds>(update_time - last_tick);
    m_scene->update(dt);

    last_tick = update_time;

    m_screen.PostEvent(ftxui::Event::Custom);
  }
}
}// namespace Sumo