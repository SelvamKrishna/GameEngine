#include <iostream>
#include "../engine/utils/color.hpp"
// #include "../engine/utils/vec2.hpp"

int main() {
  std::cout << "Hello WOrld" << std::endl;

  ColorRGBA color3 = ColorRGBA::Red();
  color3 = color3.Grayscale();

  std::cout << "Color3: (" 
            << static_cast<int>(color3.r) << ", "
            << static_cast<int>(color3.g) << ", "
            << static_cast<int>(color3.b) << ", "
            << static_cast<int>(color3.a) << ")" << std::endl;
  return 0;
}