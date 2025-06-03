#include "render.hpp"
#include "../utils/vec2.hpp"
#include <algorithm>

RenderCommand::RenderCommand() noexcept
  : texture()
  , sourceRect()
  , destRect()
  , rotation(0.0f)
  , tint(ColorRGBA::White())
  , zIndex(0) {}

RenderCommand::RenderCommand(
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

RenderCommand::RenderCommand(
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

void RenderQueue::SortByZIndex() {
  if (_dirty) std::sort(_commandBuffer.begin(), _commandBuffer.end());
  _dirty = false;
}

RenderQueue::RenderQueue() noexcept {
  _commandBuffer.reserve(DEFAULT_BUFFER_CAP);
}

void RenderQueue::AddCommand(const RenderCommand &command) noexcept {
  _commandBuffer.emplace_back(command);
  _dirty = true;
}

void RenderQueue::Flush() {
  SortByZIndex();

  for (const auto &command : _commandBuffer) {
    DrawTexturePro(
      command.texture, 
      command.sourceRect, 
      command.destRect,
      Vec2::Zero(), 
      command.rotation, 
      command.tint
    );
  }

  _commandBuffer.clear();
}