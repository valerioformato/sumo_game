#include "game/playable_character.hpp"
#include "utils/clock.hpp"
#include "utils/math.hpp"

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
    m_animation_frame = loop_increment(m_animation_frame, 0U, m_current_sprite.frames);
    m_animation_timer.restart();
  }
}

void PlayableCharacter::updatePosition(float tick)
{
  // NOTE: the ratio initial_pushback_velocity/friction_coeff determines the length of the pushback animation

  static constexpr float friction_coeff = 40.0F;
  static constexpr float pushback_threshold = 2.0F;

  if (m_in_pushback_animation) { velocity = m_pushback_velocity; }

  vec2f new_position = position + tick * velocity;
  position = collider.position = new_position;

  if (m_in_pushback_animation) {
    m_pushback_velocity -= tick * friction_coeff * normalize(m_pushback_velocity);
    if (length(m_pushback_velocity) < pushback_threshold) { m_in_pushback_animation = false; }
  }
}

void PlayableCharacter::beginPushBack(vec2f impulse)
{
  m_in_pushback_animation = true;
  m_pushback_velocity = impulse;
}

}// namespace Sumo::Game