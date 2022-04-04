#ifndef SUMO_TEXTURE_HPP
#define SUMO_TEXTURE_HPP

#include <span>
#include "utils/color.hpp"

namespace Sumo
{
	
class Texture
{
public: 
	Texture(std::span<const Color> data, std::size_t width) : 
      m_data(std::move(data)), m_width{width}
  {

  } 

  [[nodiscard]] Color at(std::size_t x, std::size_t y) const 
  {
    return m_data[y * m_width + x]; 
  }

private: 
  const std::span<const Color> m_data;
  const std::size_t m_width; 
}; 

} // namespace SUMO


#endif //SUMO_TEXTURE_HPP