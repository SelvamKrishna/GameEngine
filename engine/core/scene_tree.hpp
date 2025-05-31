#pragma once

#include "node.hpp"
#include "../systems/render.hpp"
#include <memory>

class SceneTree {
private:
  friend class App;

  std::unique_ptr<Node> _root;
  RenderQueue _renderQueue;
  
private:
  void Update();
  void FixedUpdate();
  void Render();

public:
  SceneTree() = default;
  ~SceneTree();

  SceneTree(const SceneTree &) = delete;
  SceneTree(SceneTree &&other) noexcept = default;
  SceneTree &operator=(const SceneTree &) = delete;
  SceneTree &operator=(SceneTree &&other) noexcept = default;

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

  inline void AddRenderCommand(const RenderCommand &command) noexcept {
    _renderQueue.AddCommand(command);
  }
};
