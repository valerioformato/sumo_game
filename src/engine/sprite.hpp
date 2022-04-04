#ifndef SUMO_SPRITE_HPP
#define SUMO_SPRITE_HPP

#include <span>

#include "utils/bitmap.hpp"

namespace Sumo {
struct Sprite
{
  constexpr Sprite(unsigned int dimx, unsigned int dimy, std::span<const Color> rawdata)
    : dimX{ dimx }, dimY{ dimy }, data{ rawdata } {};

  unsigned int dimX = 0;
  unsigned int dimY = 0;
  std::span<const Color> data{};
};
}// namespace Sumo

#endif