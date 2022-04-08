#ifndef SUMO_RINGSCENE_HPP
#define SUMO_RINGSCENE_HPP

#include <string_view>

#include "engine/scene.hpp"

#include "game/assets/sprites/ring.hpp"
#include "game/assets/sprites/sand_tile.hpp"

#include "game/playable_character.hpp"
#include "game/player_controller.hpp"

namespace Sumo::Game {

class RingScene : public GameScene
{
public:
  explicit RingScene();

  enum class Result { None, Win, Loss };
  Result result{ Result::None };

  void draw(Bitmap &screen_buffer);
  void update(milliseconds dt) override;
  std::vector<DrawableEntity> drawableEntities() override;


  [[nodiscard]] ftxui::ComponentDecorator eventHandler() { return m_player1_controller.event_handler; }

  [[nodiscard]] std::string_view debugInfo() { return std::string_view{ m_debug_info }; }

private:
  StaticSprite m_groundSprite{ Sprites::sand_tile };
  StaticSprite m_ringSprite{ Sprites::ring };

  PlayableCharacter m_player1{ PlayerColor::Blue };
  PlayerController m_player1_controller;

  PlayableCharacter m_player2{ PlayerColor::Red };

  std::string m_debug_info;

  static constexpr vec2f p1_starting_pos{ 120.0F, 50.0F };
  static constexpr vec2f p2_starting_pos{ 60.0F, 50.0F };

  void reset();

  // returns the vector between the two player positions
  [[nodiscard]] static vec2f setFacingDirections(PlayableCharacter &p1, PlayableCharacter &p2);
};
}// namespace Sumo::Game

#endif