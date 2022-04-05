#ifndef SUMO_PLAYERCONTROLLER_HPP
#define SUMO_PLAYERCONTROLLER_HPP

// c++ headers
#include <memory>

// dependencies headers
#include <ftxui/component/component.hpp>

// project headers
#include "game/playable_character.hpp"

namespace Sumo::Game {
struct PlayerController
{
  ftxui::ComponentDecorator eventHandler;
};
}// namespace Sumo::Game

#endif