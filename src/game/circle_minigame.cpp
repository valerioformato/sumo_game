#include <array>
#include <cmath>
#include <numbers>
#include <numeric>

#include "game/circle_minigame.hpp"

namespace Sumo::Game {

constexpr float two_pi_f = 2.0F * std::numbers::pi_v<float>;
constexpr float MIN_TARGET_SIZE = 0.05F;
constexpr float MAX_TARGET_SIZE = 0.2F;
constexpr float LINE_SPEED = two_pi_f / 2.0F;// One round trip every 3s


CircleMinigame::CircleMinigame()
  : m_target_angle{ m_unif_dist() * two_pi_f },
    m_target_size{ (MIN_TARGET_SIZE + (m_unif_dist() * (MAX_TARGET_SIZE - MIN_TARGET_SIZE))) * two_pi_f },
    m_line_angle_total{ m_unif_dist() * two_pi_f }, m_line_angle{ m_line_angle_total }
{}

void CircleMinigame::updateAnimation(float tick)
{
  static constexpr float turn_limit = 3.F * two_pi_f;

  m_line_angle_total += tick * LINE_SPEED;
  if (m_line_angle_total > turn_limit) {
    m_player_win = false;
    m_has_terminated = true;
  }
  m_line_angle = std::fmod(m_line_angle_total, two_pi_f);
}

void CircleMinigame::check()
{
  // add some tolerance, this is not dark souls after all ;)
  static constexpr float tolerance = 0.1F;
  m_player_win = std::fabs(m_line_angle - m_target_angle) < (m_target_size + tolerance);
  m_has_terminated = true;
}

std::optional<bool> CircleMinigame::result() const
{
  return (m_has_terminated ? std::optional{ m_player_win } : std::optional<bool>{});
}

void CircleMinigame::reset()
{
  m_target_angle = m_unif_dist() * two_pi_f;
  m_target_size = (MIN_TARGET_SIZE + (m_unif_dist() * (MAX_TARGET_SIZE - MIN_TARGET_SIZE))) * two_pi_f;
  m_line_angle_total = m_unif_dist() * two_pi_f;

  m_has_terminated = false;
}


StaticSprite CircleMinigame::sprite() const
{
  static auto sprite_data = Sprites::minigame_data;

  vec2u center{ 1U + Sprites::minigame.dimensions.x / 2, 1U + Sprites::minigame.dimensions.y / 2 };

  constexpr unsigned int radius = Sprites::minigame.dimensions.x / 2;

  auto pixel_at_angle = [&](float angle, float scale = 1.0F) {
    return center
           + vec2u{ static_cast<unsigned int>(scale * radius * std::cos(angle)),
               static_cast<unsigned int>(scale * radius * std::sin(angle)) };
  };

  // 0.99 to avoid overflowing sprite data
  vec2u line_end = pixel_at_angle(m_line_angle, 0.99F);// NOLINT magic numbers

  sprite_data = Sprites::minigame_data;

  // draw the line
  auto draw_line = [&](vec2i p0, vec2i p1) {
    int dx = std::abs(p1.x - p0.x);
    int sx = p0.x < p1.x ? 1 : -1;
    int dy = -std::abs(p1.y - p0.y);
    int sy = p0.y < p1.y ? 1 : -1;
    int error = dx + dy;

    while (true) {
      // plot(x0, y0)
      unsigned int idx =
        static_cast<unsigned int>(p0.x) + Sprites::minigame.dimensions.x * static_cast<unsigned int>(p0.y);
      sprite_data[idx] = ColorI32{ 255U, 0U, 0U, 255U };// NOLINT magic numbers
      if (p0.x == p1.x && p0.y == p1.y) { break; }

      int e2 = 2 * error;

      if (e2 >= dy) {
        if (p0.x == p1.x) { break; }
        error = error + dy;
        p0.x = p0.x + sx;
      }
      if (e2 <= dx) {
        if (p0.y == p1.y) { break; }
        error = error + dx;
        p0.y = p0.y + sy;
      }
    }
  };

  draw_line(static_cast<vec2i>(center), static_cast<vec2i>(line_end));

  // draw the target
  auto draw_target = [&] {
    static constexpr float dtheta = 0.05F;
    static constexpr std::array scales{ 0.9F, 0.95F, 0.99F };

    auto steps = static_cast<unsigned int>(m_target_size / dtheta);// NOLINT magic numbers

    for (unsigned int step = 0U; step < steps; ++step) {
      // basic lerp-ing...
      float theta = m_target_angle - 0.5F * m_target_size// NOLINT magic numbers
                    + static_cast<float>(step) / static_cast<float>(steps - 1U) * m_target_size;

      // draw a thick target
      for (auto scale : scales) {
        vec2u target_pixel = pixel_at_angle(theta, scale);

        unsigned int idx = target_pixel.x + Sprites::minigame.dimensions.x * target_pixel.y;
        sprite_data[idx] = ColorI32{ 255U, 0U, 0U, 255U };// NOLINT magic numbers
      }
    }
  };

  draw_target();

  return StaticSprite{ Sprites::minigame.dimensions, sprite_data };
}

}// namespace Sumo::Game