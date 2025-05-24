#include "../engine/core/app.hpp"

int main() {
  auto &app = App::Instance();
  app.Init(800, 800, "Sandox Test #1");

  while (app.IsRunning()) {
    app.Update();
    app.Render();
  }
}