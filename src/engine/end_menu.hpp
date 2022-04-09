#ifndef SUMO_END_MENU_HPP
#define SUMO_END_MENU_HPP

// dependencies headers
#include <ftxui/component/component.hpp>

namespace Sumo {
class EndMenu
{
public:
  EndMenu();

  [[nodiscard]] ftxui::Element element() const { return ftxui::vbox(m_menu_elements) | ftxui::border; };

  ftxui::Component buttons;

  void addButtons() { m_menu_elements.push_back(buttons->Render() | ftxui::center); };

private:
  ftxui::Elements m_menu_elements;
  ftxui::Elements m_title_elements;
  ftxui::Elements m_text_description;
};
}// namespace Sumo

#endif