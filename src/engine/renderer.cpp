#include "engine/renderer.hpp"
#include "engine/engine.hpp"
#include "utils/vec2.hpp"

// TODO: remove later
#include "ecs/components/sprite_component.hpp"

namespace Sumo {

ftxui::Element Renderer::DrawScene()
{
  static auto lastFrameTime = std::chrono::steady_clock::now();

  // This code actually processes the draw event

  // TODO: draw all the entities in the current scene
  const auto drawStart = std::chrono::steady_clock::now();

  using BackgroundSpriteComponent = Ecs::Components::BackgroundSpriteComponent;
  auto eM = currentScene->entityManager;

  // FIXME: this is temporary, should be generalized properly
  const auto bgDrawStart = std::chrono::steady_clock::now();
  auto groundEntity = currentScene->entities[0];
  if (eM->has_component<BackgroundSpriteComponent>(groundEntity)) {
    const auto &spriteComponent = eM->get_component<BackgroundSpriteComponent>(groundEntity).value();

    spriteComponent.Draw(*m_screenBuffer);
  }
  const auto bgDrawEnd = std::chrono::steady_clock::now();

  // draw the arena border
  // TODO: move also this to a sprite, but first requires implementing an alpha channel
  const auto arenaDrawStart = std::chrono::steady_clock::now();
  [this] {
    static const auto radius = m_screenBuffer->height() / 2UL - 2;
    static constexpr float radiusTolerance{ 1.01F };
    for (size_t iy = 0; iy < m_screenBuffer->height(); ++iy) {
      for (size_t ix = 0; ix < m_screenBuffer->width(); ++ix) {

        // compute position w.r.t. center of screen buffer
        vec2f pos{ static_cast<float>(ix), static_cast<float>(iy) };
        pos -= vec2f{ 0.5F * static_cast<float>(m_screenBuffer->width()),// NOLINT magic numbers
          0.5F * static_cast<float>(m_screenBuffer->height()) };// NOLINT magic numbers

        if (std::fabs(length(pos) - static_cast<float>(radius)) < radiusTolerance) {
          m_screenBuffer->at(ix, iy) = Color{ 255, 255, 255 };// NOLINT magic numbers
        }
      }
    }
  }();

  // draw character sprites
  const Game::PlayableCharacter &player1 = std::static_pointer_cast<Game::RingScene>(currentScene)->player1;
  Ecs::Components::SpriteComponent pSprite{ player1.sprite, false };
  vec2u pScreenPos{ static_cast<unsigned int>(player1.position.x), static_cast<unsigned int>(player1.position.y) };
  pSprite.Draw(*m_screenBuffer, pScreenPos);

  const auto lastTick = std::static_pointer_cast<Game::RingScene>(currentScene)->lastTick;
  auto playerDebugText = ftxui::text(fmt::format("{} ({}, {}) - ({}, {})",
    lastTick,
    player1.velocity.x,
    player1.velocity.y,
    player1.position.x,
    player1.position.y));

  const auto drawEnd = std::chrono::steady_clock::now();

  // now actually draw the game elements
  auto result = ftxui::hbox({ ftxui::vbox({ m_screenBuffer | ftxui::border, ftxui::text("") | ftxui::flex }),
    ftxui::vbox({ ftxui::text("Frame: " + std::to_string(m_frameCounter)),
      ftxui::text(fmt::format(
        "Total draw time: {}", std::chrono::duration_cast<std::chrono::milliseconds>(drawEnd - lastFrameTime))),
      ftxui::text(fmt::format(
        "Get scene time: {}", std::chrono::duration_cast<std::chrono::milliseconds>(bgDrawStart - drawStart))),
      ftxui::text(fmt::format(
        "Background draw time: {}", std::chrono::duration_cast<std::chrono::milliseconds>(bgDrawEnd - bgDrawStart))),
      ftxui::text(fmt::format(
        "Arena draw time: {}", std::chrono::duration_cast<std::chrono::milliseconds>(drawEnd - arenaDrawStart))),
      playerDebugText }) });

  ++m_frameCounter;
  lastFrameTime = drawEnd;

  return result;
};

}// namespace Sumo