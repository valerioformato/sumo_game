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
  ftxui::ComponentDecorator event_handler;

  struct State
  {
    ftxui::Event event;
    ftxui::Event key_event;
    std::chrono::steady_clock::time_point key_time{ std::chrono::steady_clock::now() };
  };

  State last_event;
};
}// namespace Sumo::Game

#endif