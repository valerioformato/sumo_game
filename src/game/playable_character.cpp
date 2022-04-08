#include "game/playable_character.hpp"
#include "utils/clock.hpp"

namespace Sumo::Game {
void PlayableCharacter::updateAnimation()
{
  if (m_animation_timer.elapsedTime().count() > animation_frametime.count()) {
    m_animation_frame = (m_animation_frame + 1) % m_current_sprite.frames;
    m_animation_timer.restart();
  }
}
}// namespace Sumo::Game