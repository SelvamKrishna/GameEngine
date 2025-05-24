#pragma once

#include "scene_tree.hpp"

class App {
private:
  bool _isRunning;
  SceneTree _currentScene;

private:
  App() = default;
  App(const App &) = delete;
  App &operator=(const App &) = delete;
  App(App &&) = delete;
  App &operator=(App &&) = delete;

  void Update();
  void Render();

public:
  ~App();

  static App &Instance() {
    static App instance;
    return instance;
  }

  void Init(int width, int height, const char *title);
  void Run();
  void Quit();

  inline const bool IsRunning() { return _isRunning; }
  inline void SetCurrentScene(SceneTree &currentScene) {
    _currentScene = std::move(currentScene);
  };
};