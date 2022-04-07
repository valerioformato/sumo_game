#ifndef SUMO_RINGSCENE_HPP
#define SUMO_RINGSCENE_HPP

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

  // TODO: remove later
  float last_tick{ 0 };

private:
  Sprite m_groundSprite{ Sprites::sand_tile };

  PlayableCharacter m_player1;
  PlayerController m_player1_controller;
};
}// namespace Sumo::Game

#endif