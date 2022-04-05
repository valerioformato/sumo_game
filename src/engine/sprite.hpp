#ifndef SUMO_SPRITE_HPP
#define SUMO_SPRITE_HPP

#include <span>

#include "utils/bitmap.hpp"
#include "utils/vec2.hpp"

namespace Sumo {

class Sprite
{
public:
  vec2u dimensions{ 0U, 0U };
  std::span<const Color> data{};

  [[nodiscard]] Color at(vec2u pixel) const { return data[pixel.x + dimensions.x * pixel.y]; }
};

}// namespace Sumo

#endif