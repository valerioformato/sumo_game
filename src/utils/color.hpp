#ifndef SUMO_COLOR_HPP
#define SUMO_COLOR_HPP

#include <cstdint>

namespace Sumo {
struct Color
{
  std::uint8_t R{};
  std::uint8_t G{};
  std::uint8_t B{};
  std::uint8_t A{ 255 };
};

constexpr Color alpha_blend(Color c1, Color c2, uint8_t alpha)
{
  float mix_fraction = static_cast<float>(alpha) / std::numeric_limits<uint8_t>::max();

  uint8_t r = static_cast<uint8_t>(mix_fraction * c1.R + (1.0F - mix_fraction) * c2.R);
  uint8_t g = static_cast<uint8_t>(mix_fraction * c1.G + (1.0F - mix_fraction) * c2.G);
  uint8_t b = static_cast<uint8_t>(mix_fraction * c1.B + (1.0F - mix_fraction) * c2.B);

  return Color{ r, g, b, 255U };
}
}// namespace Sumo
#endif// SUMO_COLOR_HPP