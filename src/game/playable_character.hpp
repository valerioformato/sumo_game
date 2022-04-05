#ifndef SUMO_PLAYABLECHARACTER_HPP
#define SUMO_PLAYABLECHARACTER_HPP

#include "engine/sprite.hpp"

namespace Sumo::Game {
struct PlayableCharacter
{
  Sprite sprite{ { 0U, 0U }, {} };
  vec2f position{ 0, 0 };
  vec2f velocity{ 0, 0 };
};
}// namespace Sumo::Game

#endif