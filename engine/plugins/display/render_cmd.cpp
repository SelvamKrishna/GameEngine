#include "render_cmd.hpp"

components::RenderCommand2D::RenderCommand2D() noexcept
  : texture()
  , sourceRect()
  , destRect()
  , rotation(0.0f)
  , tint(ColorRGBA::White())
  , zIndex(0) {}

components::RenderCommand2D::RenderCommand2D(
  Texture2D texture, 
  Rect sourceRect, 
  Rect destRect
) noexcept
  : texture(texture)
  , sourceRect(sourceRect)
  , destRect(destRect)
  , rotation(0.0f)
  , tint(ColorRGBA::White())
  , zIndex(0) {}

components::RenderCommand2D::RenderCommand2D(
  Texture2D texture, 
  Rect sourceRect, 
  Rect destRect, 
  float rotation, 
  ColorRGBA tint, 
  int8_t zIndex
) noexcept
  : texture(texture)
  , sourceRect(sourceRect)
  , destRect(destRect)
  , rotation(rotation)
  , tint(tint)
  , zIndex(zIndex) {}

components::RenderCommand2D::RenderCommand2D(
  std::string texturePath, 
  const components::Transform2D &transform,
  ColorRGBA tint,
  int8_t zIndex
) noexcept
  : texture(LoadTexture(texturePath.c_str()))
  , sourceRect(0.0f, 0.0f, 0.0f, 0.0f)
  , destRect(transform.position, transform.scale)
  , rotation(transform.rotation)
  , tint(tint)
  , zIndex(zIndex) {
  if (!texture.id) [[unlikely]] {
    TraceLog(LOG_WARNING, "Failed to load texture: %s", texturePath.c_str());
    return;
  }

  sourceRect.width = static_cast<float>(texture.width);
  sourceRect.height = static_cast<float>(texture.height);

  destRect.width *= static_cast<float>(texture.width);
  destRect.height *= static_cast<float>(texture.height);
}