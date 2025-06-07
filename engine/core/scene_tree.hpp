#pragma once

#include "../systems/render.hpp"
#include "node.hpp"
#include <memory>

class SceneTree {
private:
  friend class App;

  std::unique_ptr<Node> _root;
  RenderSystem2D _renderQueue;

private:
  void _FixedProcess();
  void _Process();

public:
  SceneTree() = default;
  ~SceneTree();

  SceneTree(const SceneTree &) = delete;
  SceneTree(SceneTree &&other) noexcept = default;
  SceneTree &operator=(const SceneTree &) = delete;
  SceneTree &operator=(SceneTree &&other) noexcept = default;

  void SetRoot(Node *root) noexcept {
    _root.reset(root);
    if (_root) [[likely]] _root->_Init();
  }

  [[nodiscard]] inline Node *Root() noexcept { return _root.get(); }
  [[nodiscard]] inline const Node *Root() const noexcept { return _root.get(); }

  inline void AddRenderCommand(const components::RenderCommand2D &command) noexcept {
    _renderQueue.AddCommand(command);
  }
};
