#ifndef SUMO_END_MENU_HPP
#define SUMO_END_MENU_HPP

// dependencies headers
#include <ftxui/component/component.hpp>

namespace Sumo {
class EndMenu
{
public:
  EndMenu() = default;

  [[nodiscard]] ftxui::Element element() const
  {
    auto elements = m_menu_elements;
    elements.push_back(buttons->Render() | ftxui::center);
    return ftxui::vbox(elements) | ftxui::border;
  };

  void setWin(bool win);

  ftxui::Component buttons;

private:
  ftxui::Elements m_menu_elements;
  ftxui::Elements m_title_elements;
  ftxui::Elements m_text_description;
};
}// namespace Sumo

#endif