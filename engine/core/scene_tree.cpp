#include "scene_tree.hpp"
#include "../../vendor/raylib.h"

void SceneTree::Update() {
  if (_root) [[likely]] _root->UpdateTree();
}

void SceneTree::FixedUpdate() {
  if (_root) [[likely]] _root->FixedUpdateTree();
}

void SceneTree::Render() {
  BeginDrawing();
  ClearBackground(BLACK);
  _renderQueue.Flush();
  EndDrawing();
}