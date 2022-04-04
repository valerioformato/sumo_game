#ifndef SUMO_RINGSCENE_HPP
#define SUMO_RINGSCENE_HPP

#include "ecs/components.hpp"
#include "engine/scene.hpp"
#include "game/playable_character.hpp"
#include "game/player_controller.hpp"

namespace Sumo::Game {
class RingScene : public GameScene
{
public:
  explicit RingScene(std::shared_ptr<EntityManager> entManager);

  PlayableCharacter player1;
  PlayerController player1Controller;

  void Update(std::chrono::milliseconds dt) override;

  // TODO: remove later
  float lastTick{ 0 };
};
}// namespace Sumo::Game

#endif