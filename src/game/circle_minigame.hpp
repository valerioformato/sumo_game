#ifndef SUMO_CIRCLE_MINIGAME_HPP
#define SUMO_CIRCLE_MINIGAME_HPP

#include <optional>

#include "engine/sprite.hpp"

namespace Sumo::Game {

class CircleMinigame
{
public:
  CircleMinigame() = default; 

  void updateAnimation(float tick)
  {
    
  }

  [[nodiscard]] std::optional<bool> result() const
  {
    return (m_has_terminated ? std::optional{ m_player_win } : std::optional<bool>{}); 
  }

  void reset()
  {}

private:
  static constexpr milliseconds animation_frametime{ 25.0 };
  static constexpr float radius = 20.f;  

  bool m_has_terminated{ true }; 
  bool m_player_win{ true }; 
};

}

#endif// SUMO_CIRCLE_MINIGAME_HPP
