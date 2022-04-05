#ifndef SUMO_CLOCK_HPP
#define SUMO_CLOCK_HPP

#include <chrono>


namespace Sumo {

using milliseconds = std::chrono::duration<double, std::milli>;

class Clock
{
public:
  Clock() : m_last{ std::chrono::steady_clock::now() } {}

  milliseconds restart()
  {
    auto const t = m_last;
    m_last = std::chrono::steady_clock::now();
    return m_last - t;
  }

  milliseconds elapsedTime() const { return std::chrono::steady_clock::now() - m_last; }

private:
  std::chrono::steady_clock::time_point m_last;
};

}// namespace Sumo

#endif// SUMO_CLOCK_HPP
