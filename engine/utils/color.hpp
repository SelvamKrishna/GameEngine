#pragma once

#include <cstdint>
#include <cstdlib>
#include "../../vendor/raylib.h"

struct ColorRGBA {
public:
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

public:
  constexpr ColorRGBA() noexcept : r(0), g(0), b(0), a(255) {}

  constexpr ColorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept
    : r(r), g(g), b(b), a(a) {}

  // Constructor from a raylib::Color
  constexpr ColorRGBA(const Color &color) noexcept
    : r(color.r), g(color.g), b(color.b), a(color.a) {}

  // Copy to raylib::Color from ColorRGBA
  constexpr operator Color() const noexcept { return {r, g, b, a}; }

  constexpr ColorRGBA operator+(const ColorRGBA &other) const noexcept {
    return {
      static_cast<uint8_t>(r + other.r), static_cast<uint8_t>(g + other.g),
      static_cast<uint8_t>(b + other.b), static_cast<uint8_t>(a + other.a)};
  }

  constexpr ColorRGBA operator-(const ColorRGBA &other) const noexcept {
    return {
      static_cast<uint8_t>(r - other.r), static_cast<uint8_t>(g - other.g),
      static_cast<uint8_t>(b - other.b), static_cast<uint8_t>(a - other.a)};
  }

  constexpr ColorRGBA operator*(const ColorRGBA &other) const noexcept {
    return {
      static_cast<uint8_t>(r * other.r / 255), static_cast<uint8_t>(g * other.g / 255),
      static_cast<uint8_t>(b * other.b / 255), static_cast<uint8_t>(a * other.a / 255)};
  }

  constexpr ColorRGBA operator/(const ColorRGBA &other) const noexcept {
    return {
      static_cast<uint8_t>(r / other.r), static_cast<uint8_t>(g / other.g),
      static_cast<uint8_t>(b / other.b), static_cast<uint8_t>(a / other.a)};
  }

  constexpr ColorRGBA operator+(uint8_t scalar) const noexcept {
    return {
      static_cast<uint8_t>(r + scalar), static_cast<uint8_t>(g + scalar),
      static_cast<uint8_t>(b + scalar), static_cast<uint8_t>(a + scalar)};
  }

  constexpr ColorRGBA operator-(uint8_t scalar) const noexcept {
    return {
      static_cast<uint8_t>(r - scalar), static_cast<uint8_t>(g - scalar),
      static_cast<uint8_t>(b - scalar), static_cast<uint8_t>(a - scalar)};
  }

  constexpr ColorRGBA operator*(uint8_t scalar) const noexcept {
    return {
      static_cast<uint8_t>(r * scalar / 255), static_cast<uint8_t>(g * scalar / 255),
      static_cast<uint8_t>(b * scalar / 255), static_cast<uint8_t>(a * scalar / 255)};
  }

  constexpr ColorRGBA operator/(uint8_t scalar) const noexcept {
    return {
      static_cast<uint8_t>(r / scalar), static_cast<uint8_t>(g / scalar),
      static_cast<uint8_t>(b / scalar), static_cast<uint8_t>(a / scalar)};
  }

  ColorRGBA &operator+=(const ColorRGBA &other) noexcept {
    r += other.r;
    g += other.g;
    b += other.b;
    a += other.a;
    return *this;
  }

  ColorRGBA &operator-=(const ColorRGBA &other) noexcept {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    a -= other.a;
    return *this;
  }

  ColorRGBA &operator*=(const ColorRGBA &other) noexcept {
    r = static_cast<uint8_t>(r * other.r / 255);
    g = static_cast<uint8_t>(g * other.g / 255);
    b = static_cast<uint8_t>(b * other.b / 255);
    a = static_cast<uint8_t>(a * other.a / 255);
    return *this;
  }

  ColorRGBA &operator/=(const ColorRGBA &other) noexcept {
    r = static_cast<uint8_t>(r / other.r);
    g = static_cast<uint8_t>(g / other.g);
    b = static_cast<uint8_t>(b / other.b);
    a = static_cast<uint8_t>(a / other.a);
    return *this;
  }

  ColorRGBA &operator+=(uint8_t scalar) noexcept {
    r += scalar;
    g += scalar;
    b += scalar;
    a += scalar;
    return *this;
  }

  ColorRGBA &operator-=(uint8_t scalar) noexcept {
    r -= scalar;
    g -= scalar;
    b -= scalar;
    a -= scalar;
    return *this;
  }

  ColorRGBA &operator*=(uint8_t scalar) noexcept {
    r = static_cast<uint8_t>(r * scalar / 255);
    g = static_cast<uint8_t>(g * scalar / 255);
    b = static_cast<uint8_t>(b * scalar / 255);
    a = static_cast<uint8_t>(a * scalar / 255);
    return *this;
  }

  ColorRGBA &operator/=(uint8_t scalar) noexcept {
    r = static_cast<uint8_t>(r / scalar);
    g = static_cast<uint8_t>(g / scalar);
    b = static_cast<uint8_t>(b / scalar);
    a = static_cast<uint8_t>(a / scalar);
    return *this;
  }

  constexpr bool operator==(const ColorRGBA &other) const noexcept {
    return r == other.r && g == other.g && b == other.b && a == other.a;
  }

  constexpr bool operator!=(const ColorRGBA &other) const noexcept {
    return !(*this == other);
  }

  static constexpr ColorRGBA FromHex(uint32_t hex) noexcept {
    return {
      static_cast<uint8_t>((hex >> 24) & 0xFF),
      static_cast<uint8_t>((hex >> 16) & 0xFF),
      static_cast<uint8_t>((hex >> 8) & 0xFF),
      static_cast<uint8_t>(hex & 0xFF)};
  }

  static ColorRGBA FromHex(const char *hex) noexcept {
    return FromHex(static_cast<uint32_t>(std::strtoul(hex, nullptr, 16)));
  }

  [[nodiscard]] constexpr uint32_t ToHex() const noexcept {
    return 
      (static_cast<uint32_t>(r) << 24) | (static_cast<uint32_t>(g) << 16) |
      (static_cast<uint32_t>(b) << 8) | static_cast<uint32_t>(a);
  }

  [[nodiscard]] constexpr ColorRGBA Inverted() const noexcept {
    return {
      static_cast<uint8_t>(UINT8_MAX - r), 
      static_cast<uint8_t>(UINT8_MAX - g), 
      static_cast<uint8_t>(UINT8_MAX - b), a};
  }

  [[nodiscard]] constexpr ColorRGBA Grayscale() const noexcept {
    constexpr float kLuminosityR = 0.3f;
    constexpr float kLuminosityG = 0.59f;
    constexpr float kLuminosityB = 0.11f;
    const uint8_t kGray = static_cast<uint8_t>(r * kLuminosityR + g * kLuminosityG + b * kLuminosityB);
    return {kGray, kGray, kGray, a};
  }

  inline static constexpr ColorRGBA White() noexcept { return {255, 255, 255}; }
  inline static constexpr ColorRGBA Black() noexcept { return {0, 0, 0}; }
  inline static constexpr ColorRGBA Red() noexcept { return {255, 0, 0}; }
  inline static constexpr ColorRGBA Green() noexcept { return {0, 255, 0}; }
  inline static constexpr ColorRGBA Blue() noexcept { return {0, 0, 255}; }
  inline static constexpr ColorRGBA Yellow() noexcept { return {255, 255, 0}; }
  inline static constexpr ColorRGBA Cyan() noexcept { return {0, 255, 255}; }
  inline static constexpr ColorRGBA Magenta() noexcept { return {255, 0, 255}; }
  inline static constexpr ColorRGBA Transparent() noexcept { return {0, 0, 0, 0}; }
};