// c++ headers
#include <memory>

// project headers
#include "utils/bitmap.hpp"

struct Sprite;

namespace Sumo::Ecs::Components {
class SpriteComponent
{
public:
  SpriteComponent(std::shared_ptr<Sprite> sprite, bool tiled);

  void Draw(Bitmap &screenBuffer);

private:
  std::shared_ptr<Sprite> m_sprite;
  bool m_tiled;
};

}// namespace Sumo::Ecs::Components