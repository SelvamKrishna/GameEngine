#include "../engine/core/app.hpp"

int main() {
  auto &app = App::Instance();
  app.SetWidth(800);
  app.SetHeight(800);
  app.SetTitle("Sandbox Application");
  app.Run();
  return 0;
}