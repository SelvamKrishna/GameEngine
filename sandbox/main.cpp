#include "../engine/core/app.hpp"
#include "comp.cpp"

int main() {
  // Currently in the process of making a sample game
  // Flappy Bird Clone
  App &app = App::Instance();
  app.Init(400, 600, "Sandbox Flappy Bird");

  Node *gameSceneRoot = new Node("GameSceneRoot");
  gameSceneRoot->AddChild(new Bird("Flappy"));
  gameSceneRoot->AddChild(new Pipe("Pipe"));

  SceneTree gameScene;
  gameScene.SetRoot(gameSceneRoot);

  app.SetCurrentScene(std::move(gameScene));
  app.Run();
}