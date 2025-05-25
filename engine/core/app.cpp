#include "app.hpp"
#include "../../vendor/raylib.h"
#include "../systems/time.hpp"
#include "scene_tree.hpp"

void App::Update() {
  if (WindowShouldClose()) [[unlikely]] Quit();

  constexpr float kFixedDeltaTime = 1.0f / 60.0f;

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
  _currentScene = SceneTree();
  CloseWindow();
}

void App::Init(const int width, const int height, const char *const title) {
  InitWindow(width, height, title);
  SetExitKey(KEY_NULL);
  _isRunning = true;
  _accumulator = 0.0f;
}

void App::Run() {
  TimeSystem &time = TimeSystem::Instance();

  while (_isRunning) {
    const float kDeltaTime = GetFrameTime();
    time._deltaTime = kDeltaTime;

    if (time.IsPaused()) [[unlikely]] {
      continue;
    }

    time._totalTime += kDeltaTime;
    time._frameCount++;
    _accumulator += kDeltaTime;

    Update();
    Render();
  }
}

void App::Quit() noexcept { _isRunning = false; }