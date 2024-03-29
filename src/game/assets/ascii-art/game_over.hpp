#ifndef SUMO_GAMEOVER_HPP
#define SUMO_GAMEOVER_HPP

// c++ headers
#include <array>
#include <string>

namespace Sumo::Game {
inline const std::array<std::string, 6> game_gameover = {
  R"(  _______      ___      .___  ___.  _______      ______   ____    ____  _______ .______       __  )",
  R"( /  _____|    /   \     |   \/   | |   ____|    /  __  \  \   \  /   / |   ____||   _  \     |  | )",
  R"(|  |  __     /  ^  \    |  \  /  | |  |__      |  |  |  |  \   \/   /  |  |__   |  |_)  |    |  | )",
  R"(|  | |_ |   /  /_\  \   |  |\/|  | |   __|     |  |  |  |   \      /   |   __|  |      /     |  | )",
  R"(|  |__| |  /  _____  \  |  |  |  | |  |____    |  `--'  |    \    /    |  |____ |  |\  \----.|__| )",
  R"( \______| /__/     \__\ |__|  |__| |_______|    \______/      \__/     |_______|| _| `._____|(__) )",
};
}

#endif
