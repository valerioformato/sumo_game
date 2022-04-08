#ifndef SUMO_RINGSCENE_HPP
#define SUMO_RINGSCENE_HPP

#include <string_view>

#include "engine/scene.hpp"

#include "game/assets/sprites/sand_tile.hpp"

#include "game/playable_character.hpp"
#include "game/player_controller.hpp"

namespace Sumo::Game {

class RingScene : public GameScene
{
public:
  explicit RingScene();

  void draw(Bitmap &screen_buffer);
  void update(milliseconds dt) override;
  std::vector<DrawableEntity> drawableEntities() override;


  [[nodiscard]] ftxui::ComponentDecorator eventHandler() { return m_player1_controller.event_handler; }

  [[nodiscard]] std::string_view debugInfo() { return std::string_view{ m_debug_info }; }

private:
  StaticSprite m_groundSprite{ Sprites::sand_tile };

  PlayableCharacter m_player1{ PlayerColor::Blue };
  PlayerController m_player1_controller;

  PlayableCharacter m_player2{ PlayerColor::Red };

  std::string m_debug_info;

  static void setFacingDirections(PlayableCharacter &p1, PlayableCharacter &p2);
};
}// namespace Sumo::Game

#endif