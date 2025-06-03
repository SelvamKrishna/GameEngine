#include "../engine/core/app.hpp"
#include "../engine/utils/vec2.hpp"
#include "../engine/systems/time.hpp"

class Sprite : public Node, public RenderCommand {
private:
  void Update() final {
    App::Instance().GetCurrentScene().AddRenderCommand(*this);
  }

  void FixedUpdate() final {}

public:
  Sprite(std::string name, std::string texturePath, Vec2 position, Vec2 size)
  : Node(name) {
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

class SpriteZToggle : public Node {
private:
  Sprite *sprite;

private:
  void Update() override {
    if (IsKeyPressed(KEY_SPACE)) sprite->zIndex = sprite->zIndex == 2 ? -1 : 2;
  }

public:
  SpriteZToggle(std::string name, Sprite *s) : Node(name), sprite(s) {}

  ~SpriteZToggle() override = default;
};

class SpriteMover : public Node {
private:
  Sprite *sprite;
  float speed;

private:
  void Update() final {
    Vec2 motion = Vec2::Zero();
    if (IsKeyDown(KEY_W)) {
      motion.y -= speed;
    }
    if (IsKeyDown(KEY_S)) {
      motion.y += speed;
    }
    if (IsKeyDown(KEY_A)) {
      motion.x -= speed;
    }
    if (IsKeyDown(KEY_D)) {
      motion.x += speed;
    }

    if (motion != Vec2::Zero()) {
      sprite->destRect.x += motion.x * TimeSystem::Instance().DeltaTime();
      sprite->destRect.y += motion.y * TimeSystem::Instance().DeltaTime();
    }
  }

  void FixedUpdate() final {}

public:
  SpriteMover(std::string name, Sprite *s, float moveSpeed)
  : Node(name), sprite(s), speed(moveSpeed) {
    if (!sprite) throw std::runtime_error("Sprite cannot be null");
  }

  ~SpriteMover() override = default;
};