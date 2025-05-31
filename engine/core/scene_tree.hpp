#pragma once

#include "node.hpp"
#include "../systems/render.hpp"
#include <memory>

class SceneTree {
private:
  std::unique_ptr<Node> _root;
  RenderQueue _renderQueue;

  friend class App;
  
private:
  void Update();
  void FixedUpdate();
  void Render();

public:
  SceneTree() = default;

  SceneTree(SceneTree &&other) noexcept = default;
  SceneTree &operator=(SceneTree &&other) noexcept = default;

  SceneTree(const SceneTree &) = delete;
  SceneTree &operator=(const SceneTree &) = delete;

  void SetRoot(Node *root) noexcept {
    _root.reset(root);
    if (_root) [[likely]] _root->Init();
  }

  [[nodiscard]] inline Node *GetRoot() noexcept {
    return _root.get();
  }

  [[nodiscard]] inline const Node *GetRoot() const noexcept {
    return _root.get();
  }

  [[nodiscard]] bool HasRoot() const noexcept {
    return static_cast<bool>(_root);
  }

  [[nodiscard]] inline RenderQueue &GetRenderQueue() noexcept {
    return _renderQueue;
  }
};
