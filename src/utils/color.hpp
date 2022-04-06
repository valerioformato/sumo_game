#ifndef SUMO_COLOR_HPP
#define SUMO_COLOR_HPP

#include <cstdint>
#include <numeric>

namespace Sumo {
struct Color
{
  std::uint8_t r{};
  std::uint8_t g{};
  std::uint8_t b{};
  std::uint8_t a{ std::numeric_limits<uint8_t>::max() };
};

constexpr Color alpha_blend(Color c1, Color c2, uint8_t alpha)
{
  const float mix_fraction = static_cast<float>(alpha) / std::numeric_limits<uint8_t>::max();

  uint8_t r = static_cast<uint8_t>(mix_fraction * c1.r + (1.0F - mix_fraction) * c2.r);
  uint8_t g = static_cast<uint8_t>(mix_fraction * c1.g + (1.0F - mix_fraction) * c2.g);
  uint8_t b = static_cast<uint8_t>(mix_fraction * c1.b + (1.0F - mix_fraction) * c2.b);

  return Color{ r, g, b, 255U };
}
}// namespace Sumo
#endif// SUMO_COLOR_HPP
