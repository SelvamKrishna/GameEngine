#include "render.hpp"
#include <algorithm>

void RenderSystem2D::SortByZIndex() {
  std::sort(_commandBuffer.begin(), _commandBuffer.end());
}

RenderSystem2D::RenderSystem2D() noexcept {
  _commandBuffer.reserve(DEFAULT_BUFFER_CAP);
}

void RenderSystem2D::AddCommand(const components::RenderCommand2D &command) noexcept {
  _commandBuffer.emplace_back(command);
}

void RenderSystem2D::Flush() {
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