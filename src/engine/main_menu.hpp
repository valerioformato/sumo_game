#ifndef SUMO_MAIN_MENU_HPP
#define SUMO_MAIN_MENU_HPP

// dependencies headers
#include <ftxui/component/component.hpp>

namespace Sumo {
class MainMenu
{
public:
  MainMenu();

  [[nodiscard]] ftxui::Element element() const { return ftxui::vbox(m_main_menu_elements) | ftxui::border; };

  ftxui::Component buttons;

  void addButtons() { m_main_menu_elements.push_back(buttons->Render() | ftxui::center); };

private:
  ftxui::Elements m_main_menu_elements;
  ftxui::Elements m_title_elements;
  ftxui::Elements m_text_description;
};
}// namespace Sumo

#endif