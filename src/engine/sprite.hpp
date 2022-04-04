#ifndef SUMO_SPRITE_HPP
#define SUMO_SPRITE_HPP

#include <span>

#include "utils/bitmap.hpp"
#include "engine/texture.hpp"
#include "utils/vec2.hpp"

namespace Sumo {

class Sprite
{
public: 
  friend class Renderer; 

  Sprite(const Texture *const tex, vec2i topLeft, vec2i bottomRight) : 
    m_topLeft{topLeft}, m_bottomRight{bottomRight}, m_tex{tex}
  {

  }

private: 
  vec2i m_topLeft;
  vec2i m_bottomRight; 
  const Texture * m_tex; 
};

}// namespace Sumo

#endif