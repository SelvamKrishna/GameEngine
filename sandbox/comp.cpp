#include "../engine/utils/vec2.hpp"
#include "../engine/systems/time.hpp"
#include "../engine/plugins/display/sprite.hpp"
#include <stdexcept>

class SpriteZToggle : public Node {
private:
  Sprite2D *sprite;

private:
  void _Update() override {
    if (IsKeyPressed(KEY_SPACE)) sprite->zIndex = sprite->zIndex == 2 ? -1 : 2;
  }

public:
  SpriteZToggle(std::string name, Sprite2D *s) : Node(name), sprite(s) {}

  ~SpriteZToggle() override = default;
};

class SpriteMover : public Node {
private:
  Sprite2D *sprite;
  float speed;
  Vec2 vel;

private:
  void _Update() final {
    vel.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
    vel.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);

    if (vel != Vec2::Zero()) {
      sprite->AddPosition(
        vel.Normalized() * speed * TimeSystem::Instance().DeltaTime()
      );
    }
  }

  void _FixedUpdate() final {}

public:
  SpriteMover(std::string name, Sprite2D *s, float moveSpeed)
  : Node(name), sprite(s), speed(moveSpeed) {
    if (!sprite) throw std::runtime_error("Sprite cannot be null");
  }

  ~SpriteMover() override = default;
};