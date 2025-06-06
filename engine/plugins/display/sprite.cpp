#include "sprite.hpp"
#include "../../core/app.hpp"

Sprite2D::Sprite2D(
  std::string name,
  components::RenderCommand2D renderCommand
) : Node(name) 
  , components::RenderCommand2D(renderCommand) {}

Sprite2D::~Sprite2D() { UnloadTexture(texture); }

void Sprite2D::_Update() {
  App::Instance().CurrentScene().AddRenderCommand(*this);
}

void Sprite2D::SetPosition(components::Postion2D position) noexcept {
  destRect.x = position.x;
  destRect.y = position.y;
}

void Sprite2D::AddPosition(const components::Postion2D &position) noexcept {
  destRect.x += position.x;
  destRect.y += position.y;
}

void Sprite2D::SetScale(components::Scale2D scale) noexcept {
  destRect.width = scale.x * static_cast<float>(texture.width);
  destRect.height = scale.y * static_cast<float>(texture.height);
}