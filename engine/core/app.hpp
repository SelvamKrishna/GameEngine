#pragma once

#include <string>

class App {
private:
  int _width = 500;
  int _height = 500;
  std::string _title = "Untitled";
  bool _isRunning;

private:
  App() = default;
  App(const App &) = delete;
  App &operator=(const App &) = delete;
  App(App &&) = delete;
  App &operator=(App &&) = delete;
  
  void Init();
  void Update();
  void Render();
  void Close();

public:
  ~App() = default;

  static App &Instance() {
    static App instance;
    return instance;
  }

  void Run();
  void Quit();

  inline void SetWidth(int width) { _width = width; }
  inline void SetHeight(int height) { _height = height; }
  inline void SetTitle(const char *title) { _title = title; }

  inline const int GetWidth() const { return _width; }
  inline const int GetHeight() const { return _height; }
  inline const std::string &GetTitle() const { return _title; }
};