#ifndef SUMO_PLAYABLECHARACTER_HPP
#define SUMO_PLAYABLECHARACTER_HPP

#include <map>

#include "engine/sprite.hpp"
#include "utils/clock.hpp"

#include "game/assets/sprites/blu_front.hpp"
#include "game/assets/sprites/blu_side.hpp"
#include "game/assets/sprites/red_front.hpp"
#include "game/assets/sprites/red_side.hpp"

namespace Sumo::Game {
enum class PlayerColor { Red, Blue };
enum class PlayerFacingDirection { Up, Down, Left, Right };

using AnimationMap = std::map<PlayerFacingDirection, AnimatedSprite>;
}// namespace Sumo::Game

namespace Sumo::Sprites {
constexpr auto blu_side_flipped_data = flipSpriteData<AnimatedSprite, blu_side_data.size()>(blu_side);
constexpr AnimatedSprite blu_side_flipped{ blu_side.dimensions, blu_side.frames, blu_side_flipped_data };
constexpr auto red_side_flipped_data = flipSpriteData<AnimatedSprite, red_side_data.size()>(red_side);
constexpr AnimatedSprite red_side_flipped{ red_side.dimensions, red_side.frames, red_side_flipped_data };

using Direction = Sumo::Game::PlayerFacingDirection;
inline Sumo::Game::AnimationMap blu_animations = {
  { Direction::Up, blu_front },
  { Direction::Down, blu_front },
  { Direction::Left, blu_side },
  { Direction::Right, blu_side_flipped },
};
inline Sumo::Game::AnimationMap red_animations = {
  { Direction::Up, red_front },
  { Direction::Down, red_front },
  { Direction::Left, red_side },
  { Direction::Right, red_side_flipped },
};
}// namespace Sumo::Sprites

namespace Sumo::Game {

using namespace std::chrono_literals;
class PlayableCharacter
{
public:
  explicit PlayableCharacter(PlayerColor color) : m_color{ color } {}

  vec2f position{ 0, 0 };
  vec2f velocity{ 0, 0 };

  float speed{ 15.0f };

  void updateAnimation();
  [[nodiscard]] StaticSprite currentSprite() const { return m_current_sprite.frame(m_animation_frame); }

private:
  PlayerColor m_color{ PlayerColor::Blue };
  AnimationMap m_animations = m_color == PlayerColor::Blue ? Sprites::blu_animations : Sprites::red_animations;

  Clock m_animation_timer{};
  unsigned int m_animation_frame{ 0 };
  AnimatedSprite m_current_sprite = m_animations[PlayerFacingDirection::Down];

  static constexpr milliseconds animation_frametime = 500.0ms;
};
}// namespace Sumo::Game

#endif