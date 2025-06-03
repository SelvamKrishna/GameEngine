#include "app.hpp"
#include "../../vendor/raylib.h"
#include "../systems/time.hpp"

App::~App() {
  _currentScene = SceneTree();
  CloseWindow();
}

void App::Init(const int width, const int height, std::string title) {
#ifdef PR_DEBUG
  title += " - Development Build";
#endif
  InitWindow(width, height, title.c_str());
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