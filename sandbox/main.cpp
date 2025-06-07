#include "../engine/core/app.hpp"
#include "comp.cpp"
#include <utility>

int main() {
  App &app = App::Instance();
  app.Init(800, 800, "Render System Z-Index Test");

  SceneTree sceneTree;
  Node *rootNode = new Node("Root Node");

  auto spriteMango = new Sprite2D(
    "Mango", 
    "assets/mango.jpeg",
    components::Transform2D(Vec2(300, 300)),
    0
  );

  auto spriteApple = new Sprite2D(
    "Apple", 
    "assets/apple.jpg", 
    components::Transform2D(Vec2(200, 200)),
    1
  );
  
  auto appleMover = new SpriteMover(
    "AppleMover", 
    spriteApple, 
    500.0f
  );

  auto spriteBanana = new Sprite2D(
    "Banana",
    "assets/banana.jpg", 
    components::Transform2D(Vec2(400, 400)),
    2
  );

  auto bananaZToggle = new SpriteZToggle(
    "BananaZToggle", 
    spriteBanana
  );

  rootNode->AddChild(spriteMango);

  rootNode->AddChild(spriteApple);
  rootNode->AddChild(appleMover);
  
  rootNode->AddChild(spriteBanana);
  rootNode->AddChild(bananaZToggle);

  sceneTree.SetRoot(rootNode);
  app.SetCurrentScene(std::move(sceneTree));
  app.Run();
}