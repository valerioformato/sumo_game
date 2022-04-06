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

  void Draw(Bitmap &screenBuffer);
  void Update(milliseconds dt) override;
  std::vector<DrawableEntity> DrawableEntities() override;


  [[nodiscard]] ftxui::ComponentDecorator EventHandler() { return m_player1Controller.eventHandler; }

  // TODO: remove later
  float lastTick{ 0 };

private:
  Sprite m_groundSprite{ Sprites::sand_tile };

  PlayableCharacter m_player1;
  PlayerController m_player1Controller;
};
}// namespace Sumo::Game

#endif