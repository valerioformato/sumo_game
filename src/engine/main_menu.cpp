#include "engine/main_menu.hpp"

#include "game/assets/ascii-art/title.hpp"

namespace Sumo {
MainMenu::MainMenu()
{
  for (const auto &element : Game::game_title) { m_title_elements.push_back(ftxui::text(element)); }

  m_main_menu_elements.push_back(ftxui::vbox(m_title_elements) | ftxui::center);

  m_text_description.push_back(ftxui::text("Welcome to SUMO") | ftxui::center);
  m_text_description.push_back(
    ftxui::text("This is a game made for the C++ Best Practices Game Jam by:") | ftxui::center);
  m_text_description.push_back(ftxui::text("rusticobakko, grisenti, NeeYume") | ftxui::center);
  m_text_description.push_back(ftxui::text("") | ftxui::center);
  m_text_description.push_back(
    ftxui::text("Use arrow keys to control your character and space to interact") | ftxui::center);
  m_text_description.push_back(ftxui::text("Push your opponent out of the ring before he pushes you!") | ftxui::center);
  m_text_description.push_back(ftxui::text("") | ftxui::center);
  m_text_description.push_back(
    ftxui::text("Please make sure your terminal window is in fullscreen before playing :)") | ftxui::center);

  m_main_menu_elements.push_back(ftxui::separator());

  m_main_menu_elements.push_back(ftxui::vbox(m_text_description) | ftxui::center);

  m_main_menu_elements.push_back(ftxui::text(""));
}
}// namespace Sumo