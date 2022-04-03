#ifndef SUMO_RINGSCENE_HPP
#define SUMO_RINGSCENE_HPP

#include "ecs/components.hpp"
#include "engine/scene.hpp"

namespace Sumo::Game {
class RingScene : public GameScene
{
public:
  explicit RingScene(std::shared_ptr<EntityManager> entManager);
};
}// namespace Sumo::Game

#endif