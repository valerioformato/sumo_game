#include "engine/end_menu.hpp"

#include "game/assets/ascii-art/game_over.hpp"

namespace Sumo {
EndMenu::EndMenu()
{
  for (const auto &element : Game::game_gameover) { m_title_elements.push_back(ftxui::text(element)); }

  m_menu_elements.push_back(ftxui::vbox(m_title_elements) | ftxui::center);

  m_menu_elements.push_back(ftxui::separator());

  m_menu_elements.push_back(ftxui::text(""));
}
}// namespace Sumo