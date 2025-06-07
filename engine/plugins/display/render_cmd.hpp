#pragma once

#include "../../utils/color.hpp"
#include "../../utils/rect.hpp"
#include "../default/transform.hpp"
#include <string>

namespace components {
  struct RenderCommand2D;
}

struct components::RenderCommand2D {
  Texture2D texture;
  Rect sourceRect;
  Rect destRect;
  Rotaion2D rotation = 0.0f;
  ColorRGBA tint = ColorRGBA::White();
  int8_t zIndex = 0;

  RenderCommand2D() noexcept;

  RenderCommand2D(
    Texture2D texture, 
    Rect sourceRect, 
    Rect destRect
  ) noexcept;

  RenderCommand2D(
    Texture2D texture, 
    Rect sourceRect, 
    Rect destRect, 
    float rotation, 
    ColorRGBA tint, 
    int8_t zIndex
  ) noexcept;

  RenderCommand2D(
    std::string texturePath, 
    const components::Transform2D &transform,
    ColorRGBA tint,
    int8_t zIndex
  ) noexcept;

  inline bool operator<(const RenderCommand2D &other) const noexcept {
    return zIndex < other.zIndex;
  }

  inline bool operator>(const RenderCommand2D &other) const noexcept {
    return zIndex > other.zIndex;
  }
};
