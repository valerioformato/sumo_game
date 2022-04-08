#ifndef SUMO_COLLIDER_HPP
#define SUMO_COLLIDER_HPP

#include "utils/vec2.hpp"

namespace Sumo::Game {
struct CircleCollider
{
  vec2f position;
  float radius;

  bool collision(CircleCollider other) { return distance(other.position, position) < (other.radius + radius); }
};

}// namespace Sumo::Game

#endif