#ifndef SUMO_PLAYABLECHARACTER_HPP
#define SUMO_PLAYABLECHARACTER_HPP

#include <map>

#include "engine/sprite.hpp"
#include "game/collider.hpp"
#include "utils/clock.hpp"

#include "game/assets/sprites/blu_back.hpp"
#include "game/assets/sprites/blu_front.hpp"
#include "game/assets/sprites/blu_side.hpp"
#include "game/assets/sprites/red_back.hpp"
#include "game/assets/sprites/red_front.hpp"
#include "game/assets/sprites/red_side.hpp"

namespace Sumo::Game {
enum class PlayerColor { Red, Blue };
enum class PlayerFacingDirection { Up, Down, Left, Right };

using namespace std::literals;
inline std::map<PlayerFacingDirection, std::string_view> direction_debug_name{
  { PlayerFacingDirection::Up, "up"sv },
  { PlayerFacingDirection::Down, "down"sv },
  { PlayerFacingDirection::Left, "left"sv },
  { PlayerFacingDirection::Right, "right"sv },
};

using AnimationMap = std::map<PlayerFacingDirection, AnimatedSprite>;
}// namespace Sumo::Game

namespace Sumo::Sprites {
constexpr auto blu_side_flipped_data = flipSpriteData<AnimatedSprite, blu_side_data.size()>(blu_side);
constexpr AnimatedSprite blu_side_flipped{ blu_side.dimensions, blu_side.frames, blu_side_flipped_data };
constexpr auto red_side_flipped_data = flipSpriteData<AnimatedSprite, red_side_data.size()>(red_side);
constexpr AnimatedSprite red_side_flipped{ red_side.dimensions, red_side.frames, red_side_flipped_data };

using Direction = Sumo::Game::PlayerFacingDirection;
inline Sumo::Game::AnimationMap blu_animations = {
  { Direction::Up, blu_back },
  { Direction::Down, blu_front },
  { Direction::Left, blu_side },
  { Direction::Right, blu_side_flipped },
};
inline Sumo::Game::AnimationMap red_animations = {
  { Direction::Up, red_back },
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

  PlayerFacingDirection facing_direction{ PlayerFacingDirection::Down };

  void updatePosition(float tick);

  void updateAnimation();
  [[nodiscard]] StaticSprite currentSprite() const { return m_current_sprite.frame(m_animation_frame); }

  // TODO: remove later
  [[nodiscard]] unsigned int currentAnimationFrame() const { return m_animation_frame; }

  void beginPushBack(vec2f impulse);
  void stopPushBack() { m_in_pushback_animation = false; }

private:
  PlayerColor m_color{ PlayerColor::Blue };
  PlayerFacingDirection m_last_facing_direction{ facing_direction };
  AnimationMap m_animations = m_color == PlayerColor::Blue ? Sprites::blu_animations : Sprites::red_animations;

  Clock m_animation_timer{};
  unsigned int m_animation_frame{ 0 };
  AnimatedSprite m_current_sprite = m_animations[facing_direction];

  bool m_in_pushback_animation{ false };
  vec2f m_pushback_velocity{ 0.0F, 0.0F };

  static constexpr milliseconds animation_frametime = 500.0ms;

public:
  CircleCollider collider{ position,
    0.7F * static_cast<float>(std::max(m_current_sprite.dimensions.x, m_current_sprite.dimensions.y))
      / 2.0F };// NOLINT magic numbers
};

}// namespace Sumo::Game

#endif