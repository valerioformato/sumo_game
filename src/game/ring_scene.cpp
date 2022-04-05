#include "game/ring_scene.hpp"

#include "game/assets/sprites/sand_tile.hpp"

namespace Sumo::Game {

RingScene::RingScene(GameEngine *engine) :
  GameScene(engine),
  m_groundSprite(&Sprites::sand_tile, {0,0}, {32,32}) 
{
  
}

void RingScene::update()
{
  m_engine->rendererSubmit(m_groundSprite);
}
}// namespace Sumo::Game