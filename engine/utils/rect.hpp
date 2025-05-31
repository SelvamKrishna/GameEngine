#pragma once

#include "../../vendor/raylib.h"

class Rect {
public:
  float x, y, width, height;

  constexpr Rect(float x, float y, float width, float height) noexcept
    : x(x), y(y), width(width), height(height) {}
  
  constexpr Rect() noexcept : x(0.f), y(0.f), width(0.f), height(0.f) {}

  // Constructor from raylib::Rectangle
  constexpr operator Rectangle() const noexcept {
    return {x, y, width, height};
  }

  // Copy from raylib::Rectangle to Rect
  constexpr Rect(const Rectangle &rect) noexcept
    : x(rect.x), y(rect.y), width(rect.width), height(rect.height) {}
};