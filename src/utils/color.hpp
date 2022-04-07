#ifndef SUMO_COLOR_HPP
#define SUMO_COLOR_HPP

#include "utils/math.hpp"
#include <cstdint>
#include <numeric>

namespace Sumo {

template<std::floating_point T> struct ColorF
{
  T r{}, g{}, b{}, a{ 1 };
};

template<std::integral T> struct ColorI
{
  T r{}, g{}, b{}, a{ std::numeric_limits<T>::max() };
};


using ColorI32 = ColorI<std::uint8_t>;
using ColorF32 = ColorF<float>;

template<std::floating_point T> [[nodiscard]] constexpr ColorF<T> operator/(const ColorF<T> &c, float const k)
{
  return { c.r / k, c.g / k, c.b / k, c.a };
}

template<std::floating_point T> [[nodiscard]] constexpr ColorF<T> operator*(const ColorF<T> &c, float const k)
{
  return { c.r * k, c.g * k, c.b * k, c.a };
}

template<std::floating_point T> [[nodiscard]] constexpr ColorF<T> operator+(const ColorF<T> &lhs, const ColorF<T> &rhs)
{
  return { lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, clamp(lhs.a + rhs.a, T{ 0 }, T{ 1 }) };
}

template<std::floating_point T> [[nodiscard]] constexpr ColorF<T> operator-(const ColorF<T> &lhs, const ColorF<T> &rhs)
{
  return { lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b, clamp(lhs.a - rhs.a, T{ 0 }, T{ 1 }) };
}

template<std::integral U, std::floating_point T> [[nodiscard]] constexpr ColorI<U> quantize(const ColorF<T> &c)
{
  return { static_cast<U>(clamp(c.r, T{ 0 }, T{ 1 }) * std::numeric_limits<U>::max()),
    static_cast<U>(clamp(c.g, T{ 0 }, T{ 1 }) * std::numeric_limits<U>::max()),
    static_cast<U>(clamp(c.b, T{ 0 }, T{ 1 }) * std::numeric_limits<U>::max()),
    static_cast<U>(clamp(c.a, T{ 0 }, T{ 1 }) * std::numeric_limits<U>::max()) };
}

template<std::floating_point T, std::integral U> [[nodiscard]] constexpr ColorF<T> toFPColor(const ColorI<U> &c)
{
  return { static_cast<T>(c.r) / static_cast<T>(std::numeric_limits<U>::max()),
    static_cast<T>(c.g) / static_cast<T>(std::numeric_limits<U>::max()),
    static_cast<T>(c.b) / static_cast<T>(std::numeric_limits<U>::max()),
    static_cast<T>(c.a) / static_cast<T>(std::numeric_limits<U>::max()) };
}

template<std::integral T> constexpr ColorI<T> alpha_blend(const ColorI<T> foreground, const ColorI<T> background)
{
  if (foreground.a == 0 && background.a == 0) return foreground;

  const auto bgf = toFPColor<float>(background);
  const auto fgf = toFPColor<float>(foreground);
  const auto alpha = fgf.a + (1.f - fgf.a) * bgf.a;
  const auto final_color = (fgf * fgf.a + bgf * bgf.a * (1.f - fgf.a)) / alpha;

  return quantize<std::uint8_t>(final_color);
}

}// namespace Sumo
#endif// SUMO_COLOR_HPP
