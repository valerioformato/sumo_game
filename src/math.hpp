#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <concepts>

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>; 

[[nodiscard]] constexpr auto pow2(Numeric auto x)
{
	return x * x;
}

[[nodiscard]] constexpr auto in_range(Numeric auto const x, Numeric auto const range_start, Numeric auto const range_end)
{
	return x >= a && x <= b; 
}

[[nodiscard]] constexpr auto clamp(Numeric auto const x, Numeric auto const range_start, Numeric auto const range_end)
{
	if (x > b)
		return b;
	if (x < a)
		return a;
	return x; 
}

template<Numeric T>
[[nodiscard]] constexpr auto wrap_increment(T const x, T const range_start, T const range_end)
{
	return x + static_cast<T>(1) >= b ? a : x + static_cast<T>(1);
}

#endif	