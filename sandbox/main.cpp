#include "../engine/core/app.hpp"
#include "comp.cpp"
#include <utility>

int main() {
  App &app = App::Instance();
  app.Init(800, 800, "Render System Z-Index Test");

  SceneTree sceneTree;
  Node *rootNode = new Node("Root Node");

  auto spriteMango = new Sprite("Mango", "assets/mango.jpeg", Vec2(300, 300), Vec2::One());
  spriteMango->zIndex = 0;

  auto spriteApple = new Sprite("Apple", "assets/apple.jpg", Vec2(320, 320), Vec2::One());
  spriteApple->zIndex = 1;
  auto appleMover = new SpriteMover("AppleMover", spriteApple, 500.0f);

  auto spriteBanana = new Sprite("Banana", "assets/banana.jpg", Vec2(340, 340), Vec2::One());
  spriteBanana->zIndex = 2;
  auto bananaZToggle = new SpriteZToggle("BananaZToggle", spriteBanana);

  rootNode->AttachComponent(spriteMango);

  rootNode->AttachComponent(spriteApple);
  rootNode->AttachComponent(appleMover);
  
  rootNode->AttachComponent(spriteBanana);
  rootNode->AttachComponent(bananaZToggle);

  sceneTree.SetRoot(rootNode);
  app.SetCurrentScene(std::move(sceneTree));
  app.Run();
}