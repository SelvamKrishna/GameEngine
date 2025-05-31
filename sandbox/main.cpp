#include "../engine/core/app.hpp"
#include "../engine/utils/vec2.hpp"
#include "../engine/utils/core_utils.hpp"
#include <utility>

class Sprite : public Component, public RenderCommand {
private:
  void Update() final {
    if (IsKeyPressed(KEY_W)) {
      destRect.y -= 10.0f;
    }

    App::Instance().GetCurrentScene().GetRenderQueue().AddCommand(*this);
  }
  void FixedUpdate() final {}

public:
  Sprite(std::string name, std::string texturePath, Vec2 position, Vec2 size)
  : Component(name) {
    texture = LoadTexture(texturePath.c_str());

    if (texture.id == 0)
      throw std::runtime_error("Failed to load texture");
    
    sourceRect = Rect(0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height));
    destRect = Rect(position.x, position.y, sourceRect.width * size.x, sourceRect.height *size.y);
    rotation = 0.0f;
    tint = ColorRGBA::White();
    zIndex = 0;
  }

  ~Sprite() override {
    UnloadTexture(texture);
  }
};

class BananaMover : public Component {
private:
  Sprite *sprite;

private:
  void Update() override {
    if (IsKeyPressed(KEY_SPACE)) sprite->zIndex = sprite->zIndex == 2 ? -1 : 2;
  }

public:
  BananaMover(Sprite *s) : Component("ZToggle"), sprite(s) {}
};

int main() {
  App &app = App::Instance();
  app.Init(800, 800, "Render System Z-Index Test");

  SceneTree sceneTree;
  Node *rootNode = new Node("Root Node");

  auto spriteMango = new Sprite("Mango", "assets/mango.jpeg", Vec2(300, 300), Vec2::One());
  spriteMango->zIndex = 0;
  rootNode->AddComponent(std::unique_ptr<Sprite>(spriteMango));

  auto spriteApple = new Sprite("Apple", "assets/apple.jpg", Vec2(320, 320), Vec2::One());
  spriteApple->zIndex = 1;
  rootNode->AddComponent(std::unique_ptr<Sprite>(spriteApple));

  auto spriteBanana = new Sprite("Banana", "assets/banana.jpg", Vec2(340, 340), Vec2::One());
  spriteBanana->zIndex = 2;
  rootNode->AddComponent(std::unique_ptr<Sprite>(spriteBanana));

  rootNode->AddComponent(MakeComponent<BananaMover>(spriteBanana));

  sceneTree.SetRoot(rootNode);
  app.SetCurrentScene(std::move(sceneTree));
  app.Run();
}
