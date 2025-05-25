#pragma once

#include "node.hpp"
#include <memory>

class SceneTree {
private:
  std::unique_ptr<Node> _root;

public:
  SceneTree() = default;

  void SetRoot(std::unique_ptr<Node> root);
  void Update(const float deltaTime);
  void FixedUpdate();
};