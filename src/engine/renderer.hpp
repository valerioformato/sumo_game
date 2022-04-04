#ifndef SUMO_RENDERER_HPP
#define SUMO_RENDERER_HPP

// dependencies headers
#include <ftxui/component/component.hpp>// for ScreenInteractive

// project headers
#include "engine/scene.hpp"
#include "utils/bitmap.hpp"
#include "utils/vec2.hpp"
#include "engine/sprite.hpp"

namespace Sumo {

class Renderer
{
public: 
  Renderer(std::size_t width, std::size_t height) : 
    m_frameBuffer(std::make_shared<Bitmap>(width, height))
  {

  }; 

  void begin(const Color& clearColor = Color{}); 

  void submit(const Sprite& sprite); 

  ftxui::Element end(); 

private: 
  std::shared_ptr<Bitmap> m_frameBuffer; 
}; 

}// namespace Sumo

#endif