// project headers
#include "ecs/components/background_sprite_component.hpp"
#include "ecs/components/sprite_component.hpp"
#include "ecs/entity_manager.hpp"

namespace Sumo {
using EntityManager = Ecs::EntityManager<Ecs::Components::SpriteComponent, Ecs::Components::BackgroundSpriteComponent>;
}