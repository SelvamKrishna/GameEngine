#pragma once

#include <cstdint>

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
};