#ifndef SUMO_BITMAP_HPP
#define SUMO_BITMAP_HPP

// dependencies headers
#include <ftxui/component/component.hpp>// for Slider

namespace Sumo {
struct Color
{
  std::uint8_t R{};
  std::uint8_t G{};
  std::uint8_t B{};
};

// A simple way of representing a bitmap on screen using only characters
struct Bitmap : ftxui::Node
{
  Bitmap(std::size_t width, std::size_t height)// NOLINT same typed parameters adjacent to each other
    : width_(width), height_(height)
  {}

  Color &at(std::size_t idx) { return pixels.at(idx); }
  Color &at(std::size_t x, std::size_t y) { return pixels.at(width_ * y + x); }

  void ComputeRequirement() override
  {
    requirement_ = ftxui::Requirement{
      .min_x = static_cast<int>(width_), .min_y = static_cast<int>(height_ / 2), .selected_box{ 0, 0, 0, 0 }
    };
  }

  void Render(ftxui::Screen &screen) override
  {
    for (std::size_t x = 0; x < width_; ++x) {
      for (std::size_t y = 0; y < height_ / 2; ++y) {
        auto &p = screen.PixelAt(box_.x_min + static_cast<int>(x), box_.y_min + static_cast<int>(y));
        p.character = "▄";
        const auto &top_color = at(x, y * 2);
        const auto &bottom_color = at(x, y * 2 + 1);
        p.background_color = ftxui::Color{ top_color.R, top_color.G, top_color.B };
        p.foreground_color = ftxui::Color{ bottom_color.R, bottom_color.G, bottom_color.B };
      }
    }
  }

  [[nodiscard]] auto width() const noexcept { return width_; }

  [[nodiscard]] auto height() const noexcept { return height_; }

  [[nodiscard]] auto &data() noexcept { return pixels; }

private:
  std::size_t width_;
  std::size_t height_;

  std::vector<Color> pixels = std::vector<Color>(width_ * height_, Color{});
};

}// namespace Sumo

#endif
