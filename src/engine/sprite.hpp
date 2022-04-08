#ifndef SUMO_SPRITE_HPP
#define SUMO_SPRITE_HPP

#include <cassert>
#include <span>

#include "utils/bitmap.hpp"
#include "utils/vec2.hpp"

namespace Sumo {

using SpriteIndexer = std::function<unsigned int(const vec2u pixel)>;

struct StaticSprite
{
  vec2u dimensions{ 0U, 0U };
  std::span<const ColorI32> data{};

  [[nodiscard]] ColorI32 at(const vec2u pixel) const { return data[pixel.x + dimensions.x * pixel.y]; }
};

struct AnimatedSprite
{
  vec2u dimensions{ 0U, 0U };
  unsigned int frames;
  std::span<const ColorI32> data{};

  [[nodiscard]] StaticSprite frame(unsigned int iframe) const
  {
    return StaticSprite{ dimensions,
      std::span<const ColorI32>{ &data[iframe * dimensions.x * dimensions.y], dimensions.x * dimensions.y } };
  }
};

template<class T>
concept Sprite = std::is_same_v<T, StaticSprite> || std::is_same_v<T, AnimatedSprite>;

// NOTE: we are forced to use N as a non-type template parameter here because std::span with a dynamic extent
// is not constexpr-friendly
template<Sprite T, size_t N> constexpr auto flipSpriteData(T sprite)
{
  assert(N == sprite.data.size());

  std::array<ColorI32, N> new_data;

  // for StaticSprite frames == 1
  unsigned int frames = static_cast<unsigned int>(N) / (sprite.dimensions.x * sprite.dimensions.y);

  for (unsigned int iframe = 0; iframe < frames; ++iframe) {
    for (unsigned int iy = 0U; iy < sprite.dimensions.y; ++iy) {
      for (unsigned int ix = 0U; ix < sprite.dimensions.x; ++ix) {
        new_data[iframe * (sprite.dimensions.x * sprite.dimensions.y) + (sprite.dimensions.x - ix - 1)
                 + sprite.dimensions.x * iy] =
          sprite.data[iframe * (sprite.dimensions.x * sprite.dimensions.y) + ix + sprite.dimensions.x * iy];
      }
    }
  }
  return new_data;
}
}// namespace Sumo

#endif
