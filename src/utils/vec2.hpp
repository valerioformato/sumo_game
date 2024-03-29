#ifndef SUMO_VEC2_HPP
#define SUMO_VEC2_HPP

#include "utils/math.hpp"

namespace Sumo {

template<Numeric T> struct vec2
{
  T x, y;

  vec2() = default;
  constexpr vec2(T X, T Y) : x{ X }, y{ Y } {}
  explicit constexpr vec2(T k) : x{ k }, y{ k } {}

  [[nodiscard]] bool constexpr operator==(vec2<T> const &rhs) const = default;

  vec2 constexpr &operator+=(vec2<T> const &rhs)
  {
    x += rhs.x, y += rhs.y;
    return *this;
  }

  vec2 constexpr &operator-=(vec2<T> const &rhs)
  {
    x -= rhs.x, y -= rhs.y;
    return *this;
  }

  vec2 constexpr &operator*=(T const k)
  {
    x += k, y *= k;
    return *this;
  }

  template<typename U>
  requires std::convertible_to<T, U>
  constexpr explicit operator vec2<U>() { return vec2<U>{ static_cast<U>(x), static_cast<U>(y) }; }
};

template<Numeric T> [[nodiscard]] vec2<T> constexpr operator-(vec2<T> const &rhs) { return { -rhs.x, -rhs.y }; }

template<Numeric T> [[nodiscard]] vec2<T> constexpr operator*(vec2<T> const &lhs, T k)
{
  return { lhs.x * k, lhs.y * k };
}

template<Numeric T> [[nodiscard]] vec2<T> constexpr operator*(T k, vec2<T> const &rhs)
{
  return { rhs.x * k, rhs.y * k };
}

template<Numeric T> [[nodiscard]] vec2<T> constexpr operator/(vec2<T> const &lhs, T k)
{
  return { lhs.x / k, lhs.y / k };
}

template<Numeric T> [[nodiscard]] vec2<T> constexpr operator/(T k, vec2<T> const &rhs)
{
  return { rhs.x / k, rhs.y / k };
}

template<Numeric T> [[nodiscard]] vec2<T> constexpr operator+(vec2<T> const &lhs, vec2<T> const &rhs)
{
  return { lhs.x + rhs.x, lhs.y + rhs.y };
}

template<Numeric T> [[nodiscard]] vec2<T> constexpr operator-(vec2<T> const &lhs, vec2<T> const &rhs)
{
  return { lhs.x - rhs.x, lhs.y - rhs.y };
}

template<Numeric T> [[nodiscard]] T constexpr operator^(vec2<T> const &lhs, vec2<T> const &rhs)
{
  return lhs.x * rhs.y - lhs.y * rhs.x;
}

template<std::floating_point T> [[nodiscard]] T constexpr length(vec2<T> const &v)
{
  return std::sqrt(pow2(v.x) + pow2(v.y));
}

template<std::floating_point T> [[nodiscard]] T constexpr distance(vec2<T> const &lhs, vec2<T> const &rhs)
{
  return std::sqrt(pow2(lhs.x - rhs.x) + pow2(lhs.y - rhs.y));
}

template<std::floating_point T> [[nodiscard]] vec2<T> constexpr normalize(vec2<T> const &v)
{
  auto const l = length(v);
  return { v.x / l, v.y / l };
}

using vec2f = vec2<float>;
using vec2i = vec2<int>;
using vec2u = vec2<unsigned>;
using vec2z = vec2<size_t>;

}// namespace Sumo

#endif// SUMO_VEC2_HPP