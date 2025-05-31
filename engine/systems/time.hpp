#pragma once

#include "../core/app.hpp"

class TimeSystem {
private:
  float _deltaTime;
  float _totalTime = 0.0f;
  float _timeScale = 1.0f;
  uint64_t _frameCount = 0;
  bool _isPaused = false;

  friend App;

private:
  TimeSystem() = default;
  ~TimeSystem() = default;

  TimeSystem(const TimeSystem &) = delete;
  TimeSystem(TimeSystem &&) = delete;
  TimeSystem &operator=(const TimeSystem &) = delete;
  TimeSystem &operator=(TimeSystem &&) = delete;

public:
  [[nodiscard]]
  static inline TimeSystem &Instance() noexcept {
    static TimeSystem instance;
    return instance;
  }

  inline void SetTimeScale(float scale) noexcept {
    _timeScale = scale > 0.0f ? scale : 0.0f;
  }

  [[nodiscard]] inline float DeltaTime() const noexcept { return _deltaTime; }
  [[nodiscard]] inline float TotalTime() const noexcept { return _totalTime; }
  [[nodiscard]] inline float TimeScale() const noexcept { return _timeScale; }

  [[nodiscard]] inline uint64_t FrameCount() const noexcept {
    return _frameCount;
  }

  [[nodiscard]] inline bool IsPaused() const noexcept { return _isPaused; }

  [[nodiscard]] inline uint64_t FPS() const noexcept {
    return _deltaTime > 0.0f ? static_cast<uint64_t>(1.0f / _deltaTime) : 0;
  }

  [[nodiscard]] inline float ScaledDeltaTime() const noexcept {
    return _deltaTime * _timeScale;
  }

  inline void Pause() noexcept { _isPaused = true; }
  inline void Unpause() noexcept { _isPaused = false; }
  inline void TogglePause() noexcept { _isPaused = !_isPaused; }
};
