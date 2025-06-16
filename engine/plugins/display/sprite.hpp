#pragma once

#include "../../core/node.hpp"
#include "render_cmd.hpp"

class Sprite2D : public Node, public components::RenderCommand2D {
private:
  void _Update() override;
  void _FixedUpdate() override {}

public:
  Sprite2D(
    std::string name,
    components::RenderCommand2D renderCommand
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

  inline void FlipX() noexcept { sourceRect.width *= -1; }
  inline void FlipY() noexcept { sourceRect.height *= -1; }
};