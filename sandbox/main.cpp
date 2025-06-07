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
    components::RenderCommand2DBuilder()
      .LoadTextureFromFile("assets/mango.jpeg")
      .DefaultSourceRect()
      .SetDestRect(components::Postion2D(100, 100))
      .SetZIndex(0)
    .Build()
  );

  auto spriteApple = new Sprite2D(
    "Apple",
    components::RenderCommand2DBuilder()
      .LoadTextureFromFile("assets/apple.jpg")
      .DefaultSourceRect()
      .SetDestRect(components::Postion2D(200, 200))
      .SetZIndex(1)
    .Build()
  );
  
  auto appleMover = new SpriteMover(
    "AppleMover", 
    spriteApple, 
    500.0f
  );

  auto spriteBanana = new Sprite2D(
    "Banana",
    components::RenderCommand2DBuilder()
      .LoadTextureFromFile("assets/banana.jpg")
      .DefaultSourceRect()
      .SetDestRect(components::Postion2D(300, 300))
      .SetZIndex(2)
    .Build()
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