#include "app.hpp"
#include "../../vendor/raylib.h"
#include "../systems/time.hpp"

App::~App() {
  _currentScene = SceneTree();
  CloseWindow();
}

void App::Init(const int width, const int height, std::string title) {
#ifdef PR_DEBUG
  title += " - Debug Build";
#endif
  InitWindow(width, height, title.c_str());
  SetExitKey(KEY_NULL);
  _isRunning = true;
}

void App::Run() {
  TimeSystem &timeSystem = TimeSystem::Instance();

  while (_isRunning) {
    if (WindowShouldClose()) {
      _isRunning = false;
      break;
    }

    const float kDeltaTime = GetFrameTime();
    timeSystem._deltaTime = kDeltaTime;
    timeSystem._UpdateInfo();

    if (timeSystem.IsPaused()) {
      BeginDrawing();
      EndDrawing();
      continue;
    }

    _accumulator += kDeltaTime;

    while (_accumulator >= kFixedDeltaTime) {
      _currentScene._FixedProcess();
      _accumulator -= kFixedDeltaTime;
    }

    _currentScene._Process();
  }
}