#include "app.hpp"
#include "../../vendor/raylib.h"

void App::Init() {
  InitWindow(_width, _height, _title.c_str());
  SetExitKey(0);
  _isRunning = true;
}

void App::Update() {
  if (WindowShouldClose()) _isRunning = false;
}

void App::Render() {
  BeginDrawing();
  ClearBackground(BLACK);
  EndDrawing();
}

void App::Close() {
  CloseWindow();
}

void App::Run() {
  Init();
  while (_isRunning) {
    Update();
    Render();
  }
  Close();
}

void App::Quit() {
  _isRunning = false;
}