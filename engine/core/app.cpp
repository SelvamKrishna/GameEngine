#include "app.hpp"
#include "../../vendor/raylib.h"
#include "../systems/time.hpp"
#include "scene_tree.hpp"

App::~App() {
  _currentScene = SceneTree();
  CloseWindow();
}

void App::Init(const int width, const int height, const char *const title) {
  InitWindow(width, height, title);
  SetExitKey(KEY_NULL);
  _isRunning = true;
}

void App::Run() {
  constexpr float kFixedDeltaTime = 1.0f / 60.0f;
  TimeSystem &timeSystem = TimeSystem::Instance();

  while (_isRunning) {
    const float kDeltaTime = GetFrameTime();
    timeSystem._deltaTime = kDeltaTime;

    if (timeSystem.IsPaused()) [[unlikely]] continue;

    timeSystem._totalTime += kDeltaTime;
    timeSystem._frameCount++;
    _accumulator += kDeltaTime;

    if (WindowShouldClose()) [[unlikely]] _isRunning = false;

    while (_accumulator >= kFixedDeltaTime) {
      _currentScene.FixedUpdate();
      _accumulator -= kFixedDeltaTime;
    }

    _currentScene.Update();
    _currentScene.Render();
  }
}

void App::Quit() noexcept { _isRunning = false; }