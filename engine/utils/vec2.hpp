#pragma once

#include "../../vendor/raylib.h"
#include <cmath>

struct Vec2 {
public:
  float x;
  float y;

public:
  constexpr Vec2(float x = 0.f, float y = 0.f) noexcept : x(x), y(y) {}

  constexpr operator Vector2() const noexcept { return {x, y}; }

  constexpr Vec2 operator+(const Vec2 &other) const noexcept {
    return {x + other.x, y + other.y};
  }

  constexpr Vec2 operator-(const Vec2 &other) const noexcept {
    return {x - other.x, y - other.y};
  }

  constexpr Vec2 operator*(const Vec2 &other) const noexcept {
    return {x * other.x, y * other.y};
  }

  constexpr Vec2 operator/(const Vec2 &other) const noexcept {
    return {x / other.x, y / other.y};
  }

  constexpr Vec2 operator+(float scalar) const noexcept {
    return {x + scalar, y + scalar};
  }

  constexpr Vec2 operator-(float scalar) const noexcept {
    return {x - scalar, y - scalar};
  }

  constexpr Vec2 operator*(float scalar) const noexcept {
    return {x * scalar, y * scalar};
  }

  constexpr Vec2 operator/(float scalar) const noexcept {
    return {x / scalar, y / scalar};
  }

  Vec2 &operator+=(const Vec2 &other) noexcept {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2 &operator-=(const Vec2 &other) noexcept {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec2 &operator*=(const Vec2 &other) noexcept {
    x *= other.x;
    y *= other.y;
    return *this;
  }

  Vec2 &operator/=(const Vec2 &other) noexcept {
    x /= other.x;
    y /= other.y;
    return *this;
  }

  Vec2 &operator+=(float scalar) noexcept {
    x += scalar;
    y += scalar;
    return *this;
  }

  Vec2 &operator-=(float scalar) noexcept {
    x -= scalar;
    y -= scalar;
    return *this;
  }

  Vec2 &operator*=(float scalar) noexcept {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vec2 &operator/=(float scalar) noexcept {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  constexpr bool operator==(const Vec2 &other) const noexcept {
    return x == other.x && y == other.y;
  }

  constexpr bool operator!=(const Vec2 &other) const noexcept {
    return !(*this == other);
  }

  constexpr Vec2 operator-() const noexcept { return {-x, -y}; }

  [[nodiscard]] float Length() const noexcept {
    return std::sqrt(x * x + y * y);
  }

  [[nodiscard]] Vec2 Normalize() const noexcept {
    float len = Length();
    if (len == 0.f)
      return {0.f, 0.f};
    return {x / len, y / len};
  }

  constexpr float Dot(const Vec2 &other) const noexcept {
    return x * other.x + y * other.y;
  }

  constexpr float Cross(const Vec2 &other) const noexcept {
    return x * other.y - y * other.x;
  }

  [[nodiscard]] float Distance(const Vec2 &other) const noexcept {
    return (*this - other).Length();
  }

  static constexpr Vec2 Zero() noexcept { return {0.f, 0.f}; }
  static constexpr Vec2 One() noexcept { return {1.f, 1.f}; }
  static constexpr Vec2 Up() noexcept { return {0.f, 1.f}; }
  static constexpr Vec2 Down() noexcept { return {0.f, -1.f}; }
  static constexpr Vec2 Left() noexcept { return {-1.f, 0.f}; }
  static constexpr Vec2 Right() noexcept { return {1.f, 0.f}; }
};