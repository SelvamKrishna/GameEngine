#include "scene_tree.hpp"
#include "../../vendor/raylib.h"

SceneTree::~SceneTree() {
  if (_root) [[likely]] _root->Free();
  _root.reset();
}

void SceneTree::_FixedProcess() {
  if (_root) [[likely]] _root->_FixedUpdateTree();
}

void SceneTree::_Process() {
  if (_root) [[likely]] _root->_UpdateTree();
  BeginDrawing();
  ClearBackground(BLACK);
#ifdef PR_DEBUG
  DrawFPS(10, 10);
#endif
  _renderQueue.Flush();
  EndDrawing();
}