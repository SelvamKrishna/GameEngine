#include "../engine/systems/time.hpp"
#include "../engine/utils/vec2.hpp"
#include "../engine/plugins/display/sprite.hpp"

class Bird : public Node {
private:
  static constexpr float kGravity = 980.0f;
  static constexpr float kJumpForce = -350.0f;

  components::Postion2D _position = {100.0f, 300.0f};
  float _velY = 0.0f;

  Sprite2D *_sprite = nullptr;

  void _Init() override {
    _sprite = new Sprite2D(
      "BirdSprite", 
      components::RenderCommand2DBuilder()
        .LoadTextureFromFile("assets/bird.png")
        .DefaultSourceRect()
        .SetDestRect(_position, Vec2::One() * 2.0f)
        .SetZIndex(1)
        .Build()
    );

    AddChild(_sprite);
  }

  void _Update() override {
    auto dt = TimeSystem::Instance().DeltaTime();

    _velY += kGravity * dt;

    if (IsKeyPressed(KEY_W)) _velY = kJumpForce;
    _position.y += _velY * dt;

    _sprite->SetPosition(_position);

    if (_position.y > GetScreenHeight()) TimeSystem::Instance().Pause();
  }

public:
  explicit Bird(const std::string &name) : Node(name) {}
};

class Pipe : public Node {
private:
  static constexpr float kPipeSpeed = 150.0f;

  Sprite2D *_pipeBottom = nullptr;
  Sprite2D *_pipeTop = nullptr;

  void _Init() override {
    _pipeBottom = new Sprite2D(
      "PipeSpriteBottom", 
      components::RenderCommand2DBuilder()
        .LoadTextureFromFile("assets/pipe.png")
        .DefaultSourceRect()
        .SetDestRect(Vec2::Zero(), Vec2::One() * 2.0f)
        .SetZIndex(1)
        .Build()
    );

    _pipeTop = new Sprite2D(
      "PipeSpriteTop", 
      components::RenderCommand2DBuilder()
        .LoadTextureFromFile("assets/pipe.png")
        .DefaultSourceRect()
        .SetDestRect(Vec2::Zero(), Vec2::One() * 2.0f)
        .SetZIndex(1)
        .Build()
    );

    _pipeTop->FlipY();

    AddChild(_pipeBottom);
    AddChild(_pipeTop);
    _ResetPipe();
  }

  void _Update() override {
    components::Postion2D pos = _pipeBottom->GetPosition();
    pos.x -= kPipeSpeed * TimeSystem::Instance().DeltaTime();

    if (pos.x < -_pipeBottom->destRect.width) _ResetPipe();
    else {
      _pipeBottom->SetPosition(pos);
      _pipeTop->SetPosition({
        pos.x,
        pos.y - _pipeBottom->destRect.height - 150.0f
      });
    }
  }

  void _ResetPipe() {
    _pipeBottom->SetPosition({
      static_cast<float>(GetScreenWidth()),
      static_cast<float>(GetRandomValue(50, 550))
    });
  }

public:
  explicit Pipe(const std::string &name) : Node(name) {}
};