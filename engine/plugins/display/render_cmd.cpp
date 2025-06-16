#include "render_cmd.hpp"
#include "../../../vendor/raylib.h"

using namespace components;

RenderCommand2D::RenderCommand2D() noexcept
  : texture{}
  , sourceRect{}
  , destRect{}
  , rotation{0.0f}
  , tint{ColorRGBA::White()}
  , zIndex{0} {}

RenderCommand2DBuilder &
RenderCommand2DBuilder::SetTexture(Texture2D &texture) noexcept {
  _command.texture = texture;

  if (texture.id == 0) {
    TraceLog(LOG_WARNING, "SetTexture called with invalid texture (id = 0)");
  }

  return DefaultSourceRect();
}

RenderCommand2DBuilder &
RenderCommand2DBuilder::LoadTextureFromFile(std::string texturePath) noexcept {
  _command.texture = LoadTexture(texturePath.c_str());
  if (_command.texture.id == 0) 
    TraceLog(LOG_ERROR, "Failed to load texture from path: %s", texturePath.c_str());

  return DefaultSourceRect();
}

RenderCommand2DBuilder &
RenderCommand2DBuilder::SetSourceRect(Rect sourceRect) noexcept {
  _command.sourceRect = sourceRect;
  return *this;
}

RenderCommand2DBuilder &
RenderCommand2DBuilder::DefaultSourceRect() noexcept {
  if (_command.texture.id == 0) {
    TraceLog(LOG_WARNING, "Texture not set, cannot set default source rect.");
    return *this;
  }

  _command.sourceRect = {
    0.0f,
    0.0f,
    static_cast<float>(_command.texture.width),
    static_cast<float>(_command.texture.height)
  };

  return *this;
}

RenderCommand2DBuilder &
RenderCommand2DBuilder::SetDestRect(Rect destRect) noexcept {
  _command.destRect = destRect;
  return *this;
}

RenderCommand2DBuilder &
RenderCommand2DBuilder::SetDestRect(
  components::Postion2D position, 
  components::Scale2D scale
) noexcept {
  _command.destRect = {
    position.x,
    position.y,
    _command.sourceRect.width * scale.x,
    _command.sourceRect.height * scale.y
  };

  return *this;
}

RenderCommand2DBuilder &
RenderCommand2DBuilder::SetRotation(components::Rotaion2D rotation) noexcept {
  _command.rotation = rotation;
  return *this;
}

RenderCommand2DBuilder &
RenderCommand2DBuilder::SetTint(ColorRGBA tint) noexcept {
  _command.tint = tint;
  return *this;
}

RenderCommand2DBuilder &
RenderCommand2DBuilder::SetZIndex(int8_t zIndex) noexcept {
  _command.zIndex = zIndex;
  return *this;
}

RenderCommand2D RenderCommand2DBuilder::Build() const noexcept {
  return _command;
}