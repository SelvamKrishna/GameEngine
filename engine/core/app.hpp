#pragma once


class App {
private:
  bool _isRunning;

private:
  App() = default;
  App(const App &) = delete;
  App &operator=(const App &) = delete;
  App(App &&) = delete;
  App &operator=(App &&) = delete;

public:
  ~App();

  static App &Instance() {
    static App instance;
    return instance;
  }

  void Init(int width, int height, const char *title);
  void Update();
  void Render();
  void Quit();

  inline const bool IsRunning() { return _isRunning; }
};