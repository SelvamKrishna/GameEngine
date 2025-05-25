#include "app.hpp"
#include "../../vendor/raylib.h"
#include "scene_tree.hpp"

void App::Update() {
  if (WindowShouldClose())
    Quit();

  static constexpr float kFixedDeltaTime = 1.0f / 60.0f;

  _accumulator += GetFrameTime();

  while (_accumulator >= kFixedDeltaTime) {
    _currentScene.FixedUpdate();
    _accumulator -= kFixedDeltaTime;
  }

  _currentScene.Update();
}

void App::Render() {
  BeginDrawing();
  ClearBackground(BLACK);
  EndDrawing();
}

App::~App() {
  _currentScene = std::move(SceneTree());
  CloseWindow();
}

void App::Init(int width, int height, const char *title) {
  InitWindow(width, height, title);
  SetExitKey(KEY_NULL);
  _isRunning = true;
  _accumulator = 0.0f;
}

void App::Run() {
  while (_isRunning) {
    Update();
    Render();
  }
}

void App::Quit() noexcept { _isRunning = false; }