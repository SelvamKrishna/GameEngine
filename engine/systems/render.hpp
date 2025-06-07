#pragma once

#include "../plugins/display/render_cmd.hpp"
#include <vector>

class RenderSystem2D {
private:
  static constexpr size_t DEFAULT_BUFFER_CAP = 512;

  std::vector<components::RenderCommand2D> _commandBuffer;

private:
  void SortByZIndex();

public:
  RenderSystem2D() noexcept;
  void AddCommand(const components::RenderCommand2D &command) noexcept;
  void Flush();
};