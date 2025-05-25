#pragma once

#include "node.hpp"

class SceneTree {
private:
  std::unique_ptr<Node> _root;

public:
  SceneTree() = default;

  SceneTree(SceneTree &&other) noexcept = default;
  SceneTree &operator=(SceneTree &&other) noexcept = default;

  SceneTree(const SceneTree &) = delete;
  SceneTree &operator=(const SceneTree &) = delete;

  void SetRoot(std::unique_ptr<Node> root) noexcept;

  [[nodiscard]] bool HasRoot() const noexcept { return static_cast<bool>(_root); }

  void Update();
  void FixedUpdate();
};
