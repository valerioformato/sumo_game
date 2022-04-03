#ifndef SUMO_SPRITE_HPP
#define SUMO_SPRITE_HPP

#include <span>

#include "utils/bitmap.hpp"

namespace Sumo {
class Sprite
{
public:
  constexpr Sprite(unsigned int dimx, unsigned int dimy, std::span<const uint8_t> data)
    : m_dimx{ dimx }, m_dimy{ dimy }, m_data{ data } {};

private:
  unsigned int m_dimx;
  unsigned int m_dimy;
  std::span<const uint8_t> m_data;
};
}// namespace Sumo

#endif