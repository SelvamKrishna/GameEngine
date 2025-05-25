#include "../engine/core/app.hpp"
#include <iostream>
#include <string>

class Sample : public Node {
public:
  Sample(const std::string &name) : Node(name) {}

  void Init() override {
    std::cout << "created: " << _name << "\n";
  }

  void Update(const float deltaTime) override {
    std::cout << "updating: " << _name << "\n";
  }

  void FixedUpdate() override {
    std::cout << "fixed updating: " << _name << "\n";
  }
};

int main() {
  SceneTree tree;

  auto node = Node::Create("Sample root");
  node->AddChild(Node::Create("Sample child"));

  tree.SetRoot(node.get());

  App &app = App::Instance();
  app.Init(800, 800, "Sandbox #1");
  app.SetCurrentScene(tree);
  app.Run();
}