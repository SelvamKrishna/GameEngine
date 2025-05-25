#include "scene_tree.hpp"

void SceneTree::SetRoot(std::unique_ptr<Node> root) noexcept {
  _root = std::move(root);
  if (_root) _root->Init();
}

void SceneTree::Update() {
  if (_root) _root->UpdateTree();
}

void SceneTree::FixedUpdate() {
  if (_root) _root->FixedUpdateTree();
}