#include "../engine/core/app.hpp"
#include <iostream>
#include <string>

class Sample : public Node {
public:
  Sample(const std::string &name) : Node(name) {}

  void Start() override {
    std::cout << "created: " << _name << "\n";
  }

  void Update(const float deltaTime) override {
    std::cout << "updating: " << _name << "\n";
  }

  void FixedUpdate(const float deltaTime) override {
  }
};

int main() {
  SceneTree tree;

  Sample *node = new Sample("sample root");
  node->AddChild(new Sample("sample child 1"));

  tree.SetRoot(node);

  App &app = App::Instance();
  app.Init(800, 800, "Sandbox #1");
  app.SetCurrentScene(tree);
  app.Run();
}