#include "app.hpp"
#include "../../vendor/raylib.h"

void App::Init(int width, int height, const char *title) {
  InitWindow(width, height, title);
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

void App::Quit() {
  _isRunning = false;
}

App::~App() {
  CloseWindow();
}