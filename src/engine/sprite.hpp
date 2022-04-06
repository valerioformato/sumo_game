#ifndef SUMO_SPRITE_HPP
#define SUMO_SPRITE_HPP

#include <span>

#include "utils/bitmap.hpp"
#include "utils/vec2.hpp"

namespace Sumo {

struct Sprite
{
  vec2u dimensions{ 0U, 0U };
  std::span<const Color> data{};

  [[nodiscard]] Color at(const vec2u pixel) const { return data[pixel.x + dimensions.x * pixel.y]; }
};

struct AnimatedSprite
{
  vec2u dimensions{ 0U, 0U };
  unsigned int frames;
  std::span<const Color> data{};

  [[nodiscard]] Sprite frame(unsigned int iframe) const
  {
    return Sprite{ dimensions,
      std::span<const Color>{ &data[iframe * dimensions.x * dimensions.y], dimensions.x * dimensions.y } };
  }
};

}// namespace Sumo

#endif
