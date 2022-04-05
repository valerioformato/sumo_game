// c++ headers
#include <array>
#include <functional>
#include <iostream>
#include <random>

// dependencies headers
#include <docopt/docopt.h>
#include <ftxui/component/captured_mouse.hpp>// for ftxui
#include <ftxui/component/component.hpp>// for Slider
#include <ftxui/component/screen_interactive.hpp>// for ScreenInteractive

// project headers

// This file will be generated automatically when you run the CMake
// configuration step. It creates a namespace called `sumo_game`. You can modify
// the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>

#include "engine/engine.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
{
  Sumo::GameEngine engine;
  engine.run();
}
