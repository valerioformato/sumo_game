#ifndef SUMO_CLOCK_HPP
#define SUMO_CLOCK_HPP

#include <chrono>

namespace Sumo
{

class Clock
{
public: 
  Clock() : 
    m_last{std::chrono::steady_clock::now()}
  {

  }
  
  std::chrono::nanoseconds restart()
  {
    auto const t = m_last; 
    m_last = std::chrono::steady_clock::now(); 
    return m_last - t;  
  }

  std::chrono::nanoseconds elapsedTime() const
  {
    return std::chrono::steady_clock::now() - m_last; 
  }

private: 
  std::chrono::steady_clock::time_point m_last; 
};

} // namespace Sumo

#endif //SUMO_CLOCK_HPP
