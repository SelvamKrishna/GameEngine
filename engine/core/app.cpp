#include "app.hpp"
#include "../../vendor/raylib.h"
#include <memory>

void App::Update() {
  if (WindowShouldClose()) Quit();

  static constexpr float kFixedDeltaTime = 1.0f / 60.0f;
  const float kDeltaTime = GetFrameTime();

  _accumulator += kDeltaTime;

  while (_accumulator >= kFixedDeltaTime) {
    _currentScene.FixedUpdate();
    _accumulator -= kFixedDeltaTime;
  }

  _currentScene.Update(kDeltaTime);
}

void App::Render() {
  BeginDrawing();
  ClearBackground(BLACK);
  EndDrawing();
}

App::~App() {
  CloseWindow();
  _currentScene.SetRoot(std::unique_ptr<Node>{});
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

void App::Quit() { _isRunning = false; }