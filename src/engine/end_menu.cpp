#include "engine/end_menu.hpp"

#include "game/assets/ascii-art/game_over.hpp"
#include "game/assets/ascii-art/you_win.hpp"

namespace Sumo {
void EndMenu::setWin(bool win)
{
  m_title_elements.clear();
  m_menu_elements.clear();

  const auto &big_text = win ? Game::you_win : Game::game_gameover;

  for (const auto &element : big_text) { m_title_elements.push_back(ftxui::text(element)); }

  m_menu_elements.push_back(ftxui::vbox(m_title_elements) | ftxui::center);
  m_menu_elements.push_back(ftxui::separator());
  m_menu_elements.push_back(ftxui::text(""));
}
}// namespace Sumo