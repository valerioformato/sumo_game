#include "game/playable_character.hpp"
#include "utils/clock.hpp"

namespace Sumo::Game {
void PlayableCharacter::updateAnimation()
{
  if (facing_direction != m_last_facing_direction) {
    m_current_sprite = m_animations[facing_direction];
    m_animation_frame = 0U;
    m_animation_timer.restart();

    m_last_facing_direction = facing_direction;
  }

  if (m_animation_timer.elapsedTime().count() > animation_frametime.count()) {
    m_animation_frame = (m_animation_frame + 1) % m_current_sprite.frames;
    m_animation_timer.restart();
  }
}

void PlayableCharacter::updatePosition(float tick)
{
  vec2f new_position = position + tick * velocity;
  position = collider.position = new_position;
}
}// namespace Sumo::Game