#ifndef SUMO_PLAYABLECHARACTER_HPP
#define SUMO_PLAYABLECHARACTER_HPP

#include <variant>

#include "engine/sprite.hpp"

namespace Sumo::Game {
struct PlayableCharacter
{
  Sprite sprite;
  vec2f position{ 0, 0 };
  vec2f velocity{ 0, 0 };
  unsigned int animation_frame{ 0 };
};
}// namespace Sumo::Game

#endif