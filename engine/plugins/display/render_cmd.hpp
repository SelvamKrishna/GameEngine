#pragma once

#include "../../utils/color.hpp"
#include "../../utils/rect.hpp"
#include "../default/transform.hpp"
#include <string>

namespace components {
struct RenderCommand2D;
class RenderCommand2DBuilder;
}

struct components::RenderCommand2D {
  Texture2D texture;
  Rect sourceRect;
  Rect destRect;
  Rotaion2D rotation = 0.0f;
  ColorRGBA tint = ColorRGBA::White();
  int32_t zIndex = 0;

  RenderCommand2D() noexcept;

  inline bool operator<(const RenderCommand2D &other) const noexcept {
    return zIndex < other.zIndex;
  }

  inline bool operator>(const RenderCommand2D &other) const noexcept {
    return zIndex > other.zIndex;
  }
};

class components::RenderCommand2DBuilder {
private:
  RenderCommand2D _command;

public:
  RenderCommand2DBuilder &SetTexture(Texture2D &texture) noexcept;
  RenderCommand2DBuilder &LoadTextureFromFile(std::string texturePath) noexcept;
  RenderCommand2DBuilder &SetSourceRect(Rect sourceRect) noexcept;
  RenderCommand2DBuilder &DefaultSourceRect() noexcept;
  RenderCommand2DBuilder &SetDestRect(Rect destRect) noexcept;
  RenderCommand2DBuilder &SetDestRect(
    components::Postion2D position = Vec2::Zero(), 
    components::Scale2D scale = Vec2::One()
  ) noexcept;
  RenderCommand2DBuilder &SetRotation(components::Rotaion2D rotation) noexcept;
  RenderCommand2DBuilder &SetTint(ColorRGBA tint) noexcept;
  RenderCommand2DBuilder &SetZIndex(int8_t zIndex) noexcept;

  RenderCommand2D Build() const noexcept;
};