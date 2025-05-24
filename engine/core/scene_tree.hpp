#pragma once

#include "node.hpp"

class SceneTree {
private:
  Node *_root = nullptr;

public:
  SceneTree() = default;
  ~SceneTree() { if (_root) delete _root; }

  void SetRoot(Node *root) {
    if (_root) delete _root;
    _root = root;
    _root->Start();
  }

  void Update(const float deltaTime) { if (_root) _root->UpdateTree(deltaTime); }
  void FixedUpdate(const float deltaTime) { if (_root) _root->FixedUpdateTree(deltaTime); }
};