#pragma once

#include "../../core/node.hpp"
#include "render_cmd.hpp"

class Sprite2D : public Node, public components::RenderCommand2D {
private:
  void Update() override;
  void FixedUpdate() override {}

public:
  Sprite2D(
    std::string name, 
    std::string texturePath,
    const components::Transform2D &transform, int8_t zIndex = 0,
    ColorRGBA tint = ColorRGBA::White()
  );

  ~Sprite2D() override;

  inline void Crop(const Rect &sourceRect) noexcept {
    this->sourceRect = sourceRect;
  }

  void SetPosition(components::Postion2D position) noexcept;
  void AddPosition(const components::Postion2D &position) noexcept;

  [[nodiscard]] inline components::Postion2D GetPosition() const noexcept {
    return {destRect.x, destRect.y};
  }

  void SetScale(components::Scale2D scale) noexcept;

  [[nodiscard]] inline components::Scale2D GetScale() const noexcept {
    return {
      destRect.width / static_cast<float>(texture.width),
      destRect.height / static_cast<float>(texture.height)
    };
  }
};