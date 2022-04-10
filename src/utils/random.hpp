#ifndef SUMO_RANDOM_HPP
#define SUMO_RANDOM_HPP

#include <random>
#include <limits>
#include <type_traits>

namespace Sumo {

template<Numeric T> class UniformRand
{
public:
  UniformRand(T i = std::numeric_limits<T>::min(), T j = std::numeric_limits<T>::max(), unsigned seed = 0)
    : rand_engine{ seed }, dist{ i, j }
  {
    
  }

  [[nodiscard]] T operator()() { return dist(rand_engine); }

private:
  std::default_random_engine rand_engine;
  std::conditional_t<std::is_floating_point_v<T>, std::uniform_real_distribution<T>, std::uniform_int_distribution<T>>
    dist;
};

} // namespace Sumo

#endif// SUMO_RANDOM_HPP

