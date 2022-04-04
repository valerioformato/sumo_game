#ifndef SUMO_COLOR_HPP
#define SUMO_COLOR_HPP

#include <cstdint>

struct Color
{
  std::uint8_t R{};
  std::uint8_t G{};
  std::uint8_t B{};
  std::uint8_t A{}; 
};

#endif //SUMO_COLOR_HPP