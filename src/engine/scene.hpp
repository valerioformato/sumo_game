#ifndef SUMO_SCENE_HPP
#define SUMO_SCENE_HPP

// project headers
#include "utils/bitmap.hpp"


namespace Sumo {

class GameEngine; 

class GameScene
{
public:
  explicit GameScene(GameEngine *engine) : m_engine{engine}
  {
    
  }

  virtual void update() = 0; 

protected:
	GameEngine* m_engine; 
};
}// namespace Sumo

#endif