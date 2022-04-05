#ifndef SUMO_RINGSCENE_HPP
#define SUMO_RINGSCENE_HPP

#include "engine/scene.hpp"
#include "engine/sprite.hpp"
#include "engine/engine.hpp"

namespace Sumo::Game {
class RingScene : public GameScene
{
public:
  explicit RingScene(GameEngine* engine);

  void update() override;

private:
  Sprite m_groundSprite; 
};
}// namespace Sumo::Game

#endif