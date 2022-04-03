#include "engine/renderer.hpp"
#include "engine/engine.hpp"
#include "utils/vec2.hpp"


namespace Sumo {

ftxui::Element Renderer::DrawScene()
{
  static auto lastFrameTime = std::chrono::steady_clock::now();

  // This code actually processes the draw event

  // TODO: draw all the entities in the current scene

  // FIXME: as soon as we have an ECS move all the drawcode to a SpriteComponent or something equivalent

  // draw the "sand"
  // [this] {
  //   for (size_t ix = 0; ix < m_screenBuffer->width(); ++ix) {
  //     for (size_t iy = 0; iy < m_screenBuffer->height(); ++iy) { m_screenBuffer->at(ix, iy) = GameScene::sandColor; }
  //   }
  // }();

  using SpriteComponent = Ecs::Components::SpriteComponent;
  auto eM = currentScene->entityManager;

  // FIXME: this is temporary, should be generalized properly
  auto groundEntity = currentScene->entities[0];
  if (eM->has_component<SpriteComponent>(groundEntity)) {
    auto spriteComponent = eM->get_component<SpriteComponent>(groundEntity).value();
    spriteComponent.Draw(*m_screenBuffer, { 0U, 0U });
  }

  // draw the arena border
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

  const auto drawEnd = std::chrono::steady_clock::now();

  // now actually draw the game elements
  auto result = ftxui::hbox({ ftxui::vbox({ m_screenBuffer | ftxui::border, ftxui::text("") | ftxui::flex }),
    ftxui::vbox({ ftxui::text("Frame: " + std::to_string(m_frameCounter)),
      ftxui::text(fmt::format(
        "Draw time: {}", std::chrono::duration_cast<std::chrono::milliseconds>(drawEnd - lastFrameTime))) }) });

  ++m_frameCounter;
  lastFrameTime = drawEnd;

  return result;
};

}// namespace Sumo