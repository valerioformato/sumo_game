#ifndef SUMO_RINGSCENE_HPP
#define SUMO_RINGSCENE_HPP

#include <string_view>

#include "engine/scene.hpp"

#include "game/assets/sprites/ring.hpp"
#include "game/assets/sprites/sand_tile.hpp"

#include "game/circle_minigame.hpp"
#include "game/playable_character.hpp"
#include "game/player_controller.hpp"

namespace Sumo::Game {

class RingScene : public GameScene
{
public:
  explicit RingScene();

  static constexpr unsigned int max_rounds{ 3U };

  enum class Result { None, Win, Loss };
  std::array<Result, max_rounds> results{ Result::None };

  void draw(Bitmap &screen_buffer);
  void update(milliseconds dt) override;
  [[nodiscard]] std::vector<DrawableEntity> drawableEntities() override;


  // did it like this cause maybe one day we'll support pvp mode :)
  [[nodiscard]] std::vector<ftxui::ComponentDecorator> eventHandlers() override
  {
    return { m_player1_controller.event_handler };
  }

  [[nodiscard]] const std::vector<std::string> &debugInfo() const { return m_debug_info; }

  void start() override { reset(true); };
  [[nodiscard]] std::optional<bool> finalResult() const override;

private:
  StaticSprite m_groundSprite{ Sprites::sand_tile };
  StaticSprite m_ringSprite{ Sprites::ring };

  PlayableCharacter m_player1{ PlayerColor::Blue };
  PlayerController m_player1_controller;

  PlayableCharacter m_player2{ PlayerColor::Red };

  CircleMinigame m_minigame;
  bool m_in_minigame{ false };
  std::chrono::steady_clock::time_point m_last_minigame_end;

  std::vector<std::string> m_debug_info{};

  enum class PlayerState { Free, Locked };
  PlayerState m_players_state{ PlayerState::Free };

  enum class PushBackStyle { Impulse, Constant };

  static constexpr vec2f p1_starting_pos{ 120.0F, 50.0F };
  static constexpr vec2f p2_starting_pos{ 60.0F, 50.0F };


  void updatePlayers(const float tick);
  void startMinigame();
  void updateMinigame(const float tick);

  unsigned int m_rounds{ 0 };// round! see? :D

  void reset(bool erase_rounds = false);

  // returns the vector between the two player positions
  [[nodiscard]] static vec2f setFacingDirections(PlayableCharacter &p1, PlayableCharacter &p2);

  static void playerPushBack(PlayableCharacter &pushing_player, PlayableCharacter &pushed_player, PushBackStyle style);
};
}// namespace Sumo::Game

#endif