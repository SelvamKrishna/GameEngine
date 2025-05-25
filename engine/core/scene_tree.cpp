#include "scene_tree.hpp"
#include <utility>

void SceneTree::SetRoot(std::unique_ptr<Node> root) {
  _root = std::move(root);
}

void SceneTree::Update(const float deltaTime) {
  if (_root) _root->UpdateTree(deltaTime);
}

void SceneTree::FixedUpdate() {
  if (_root) _root->FixedUpdateTree();
}