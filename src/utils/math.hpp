#ifndef SUMO_MATH_HPP
#define SUMO_MATH_HPP

#include <cmath>
#include <concepts>

namespace Sumo {
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

[[nodiscard]] constexpr auto pow2(Numeric auto x) { return x * x; }

[[nodiscard]] constexpr auto
  in_range(Numeric auto const x, Numeric auto const range_start, Numeric auto const range_end)
{
  return x >= range_start && x < range_end;
}

[[nodiscard]] constexpr auto clamp(Numeric auto const x, Numeric auto const range_start, Numeric auto const range_end)
{
  if (x > range_end) return range_end;
  if (x < range_start) return range_start;
  return x;
}

template<Numeric T> [[nodiscard]] constexpr auto loop_increment(T const x, T const range_start, T const range_end)
{
  return x + static_cast<T>(1) >= range_end ? range_start : x + static_cast<T>(1);
}

}// namespace Sumo

#endif// SUMO_MATH_HPP