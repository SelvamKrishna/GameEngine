#include "app.hpp"
#include "../../vendor/raylib.h"

void App::Update() {
  if (WindowShouldClose()) Quit();
  _currentScene.Update(GetFrameTime());
}

void App::Render() {
  BeginDrawing();
  ClearBackground(BLACK);
  EndDrawing();
}

App::~App() {
  CloseWindow();
  _currentScene.SetRoot(nullptr);
}

void App::Init(int width, int height, const char *title) {
  InitWindow(width, height, title);
  _isRunning = true;
}

void App::Run() {
  while (_isRunning) {
    Update();
    Render();
  }
}

void App::Quit() { _isRunning = false; }