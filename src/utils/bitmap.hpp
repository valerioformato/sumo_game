#ifndef SUMO_BITMAP_HPP
#define SUMO_BITMAP_HPP

// dependencies headers
#include <ftxui/component/component.hpp>// for Slider

#include "utils/color.hpp"

namespace Sumo {

// A simple way of representing a bitmap on screen using only characters
struct Bitmap final : ftxui::Node
{
  Bitmap(const std::size_t width, const std::size_t height)// NOLINT same typed parameters adjacent to each other
    : m_width(width), m_height(height)
  {}

  Color &at(const std::size_t idx) { return m_pixels.at(idx); }
  Color &at(const std::size_t x, const std::size_t y) { return m_pixels.at(m_width * y + x); }

  void ComputeRequirement() override
  {
    requirement_ = ftxui::Requirement{
      .min_x = static_cast<int>(m_width), .min_y = static_cast<int>(m_height / 2), .selected_box{ 0, 0, 0, 0 }
    };
  }

  void Render(ftxui::Screen &screen) override
  {
    for (std::size_t x = 0; x < m_width; ++x) {
      for (std::size_t y = 0; y < m_height / 2; ++y) {
        auto &p = screen.PixelAt(box_.x_min + static_cast<int>(x), box_.y_min + static_cast<int>(y));
        p.character = "▄";
        const auto &top_color = at(x, y * 2);
        const auto &bottom_color = at(x, y * 2 + 1);
        p.background_color = ftxui::Color{ top_color.r, top_color.g, top_color.b };
        p.foreground_color = ftxui::Color{ bottom_color.r, bottom_color.g, bottom_color.b };
      }
    }
  }

  [[nodiscard]] auto width() const noexcept { return m_width; }

  [[nodiscard]] auto height() const noexcept { return m_height; }

  [[nodiscard]] auto &data() noexcept { return m_pixels; }

private:
  std::size_t m_width;
  std::size_t m_height;

  std::vector<Color> m_pixels = std::vector<Color>(m_width * m_height, Color{});
};

}// namespace Sumo

#endif
