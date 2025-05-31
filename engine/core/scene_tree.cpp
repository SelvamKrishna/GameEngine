#include "scene_tree.hpp"
#include "../../vendor/raylib.h"

SceneTree::~SceneTree() {
  if (_root) [[likely]] _root->Free();
  _root.reset();
}

void SceneTree::Update() {
  if (_root) [[likely]] _root->UpdateTree();
}

void SceneTree::FixedUpdate() {
  if (_root) [[likely]] _root->FixedUpdateTree();
}

void SceneTree::Render() {
  BeginDrawing();
  ClearBackground(BLACK);
#ifdef PR_DEBUG
  DrawFPS(10, 10);
#endif
  _renderQueue.Flush();
  EndDrawing();
}