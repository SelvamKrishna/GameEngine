#pragma once

#include "../plugins/display/render_cmd.hpp"
#include <vector>

class RenderSystem2D {
private:
  std::vector<components::RenderCommand2D> _commandBuffer;
  bool _dirty = false;

  static constexpr size_t DEFAULT_BUFFER_CAP = 512;

private:
  void SortByZIndex();

public:
  RenderSystem2D() noexcept;
  void AddCommand(const components::RenderCommand2D &command) noexcept;
  void Flush();
};