#pragma once

#include "../../utils/vec2.hpp"
#include <algorithm>

namespace components {
using Postion2D = Vec2;
using Scale2D = Vec2;
using Rotaion2D = float;

struct Transform2D;
}

struct components::Transform2D {
  Postion2D position;
  Scale2D scale;
  Rotaion2D rotation;

  Transform2D() : position(Vec2::Zero()), scale(Vec2::One()), rotation(0.0f) {}

  Transform2D(const Postion2D &position)
    : position(position), scale(Vec2::One()), rotation(0.0f) {}

  Transform2D(
    const Postion2D &position, 
    const Scale2D &scale,
    Rotaion2D rotation
  ) : position(position), scale(scale), rotation(rotation) {}

  inline void Translate(const Postion2D &translation) noexcept { position += translation; }
  inline void Scale(const Scale2D &scaling) noexcept { scale *= scaling; }

  inline void Rotate(Rotaion2D angle) noexcept {
    rotation = std::clamp(rotation + angle, 0.0f, 360.0f);
  }
};