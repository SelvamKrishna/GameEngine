#pragma once

#include "scene_tree.hpp"
#include <string>

class App {
private:
  static constexpr float kFixedFrameRate = 60.0f;
  static constexpr float kFixedDeltaTime = 1.0f / kFixedFrameRate;

  SceneTree _currentScene;
  float _accumulator = 0.0f;
  bool _isRunning = false;

private:
  App() = default;
  ~App();

  App(const App &) = delete;
  App(App &&) = delete;
  App &operator=(const App &) = delete;
  App &operator=(App &&) = delete;

public:
  [[nodiscard]]
  static inline App &Instance() noexcept {
    static App instance;
    return instance;
  }

  void Init(int width, int height, std::string title);
  void Run();
  inline void Quit() noexcept { _isRunning = false; }

  [[nodiscard]] inline bool IsRunning() const noexcept {
    return _isRunning;
  }

  void SetCurrentScene(const SceneTree &) = delete;
  inline void SetCurrentScene(SceneTree &&currentScene) noexcept {
    _currentScene = std::move(currentScene);
  }

  [[nodiscard]] inline SceneTree &CurrentScene() noexcept {
    return _currentScene;
  }
};