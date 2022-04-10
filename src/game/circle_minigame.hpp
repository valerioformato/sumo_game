#ifndef SUMO_CIRCLE_MINIGAME_HPP
#define SUMO_CIRCLE_MINIGAME_HPP

#include <optional>

#include "engine/sprite.hpp"
#include "game/assets/sprites/minigame.hpp"
#include "utils/clock.hpp"
#include "utils/random.hpp"

namespace Sumo::Game {

class CircleMinigame
{
public:
  CircleMinigame();

  void updateAnimation(float tick);

  void check();

  [[nodiscard]] std::optional<bool> result() const;

  void reset();

  [[nodiscard]] StaticSprite sprite() const;

private:
  UniformRand<float> m_unif_dist{ 0.0F, 1.0F };

  bool m_has_terminated{ false };
  bool m_player_win{ true };

  float m_target_angle;
  float m_target_size;
  float m_line_angle_total;
  float m_line_angle;

  unsigned int m_radius{ 0U };
  vec2u m_center{ 0U, 0U };

  vec2u pixelAtAngle(float angle, float scale = 1.0F) const;
  void drawTarget(std::span<ColorI32> buffer) const;
  static void drawLine(std::span<ColorI32> buffer, vec2i p0, vec2i p1);
};

}// namespace Sumo::Game

#endif// SUMO_CIRCLE_MINIGAME_HPP
