#pragma once

#include "../../vendor/raylib.h"
#include "../utils/color.hpp"
#include "../utils/rect.hpp"
#include <vector>

struct RenderCommand {
  Texture2D texture;
  Rect sourceRect;
  Rect destRect;
  float rotation = 0.0f;
  ColorRGBA tint = ColorRGBA::White();
  int8_t zIndex = 0;

  RenderCommand() noexcept;

  RenderCommand(
    Texture2D texture, 
    Rect sourceRect, 
    Rect destRect
  ) noexcept;

  RenderCommand(
    Texture2D texture, 
    Rect sourceRect, 
    Rect destRect, 
    float rotation, 
    ColorRGBA tint, 
    int8_t zIndex
  ) noexcept;

  bool operator<(const RenderCommand &other) const noexcept {
    return zIndex < other.zIndex;
  }
};

class RenderQueue {
private:
  std::vector<RenderCommand> _commandBuffer;
  bool _dirty = false;

  static constexpr size_t DEFAULT_BUFFER_CAP = 512;

private:
  void SortByZIndex();

public:
  RenderQueue() noexcept;
  void AddCommand(const RenderCommand &command) noexcept;
  void Flush();
};