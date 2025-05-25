#include "../engine/core/app.hpp"
#include "../engine/utils/core_utils.hpp"
#include <iostream>

class Sample : public Node {
private:
  int flag;

public:
  Sample(const std::string &name) : Node(name) {
    std::cout << "created: " << _name << "\n";
  }

  void Init() final {
    flag = 0;    
  }

  void Update() final {
    // std::cout << "updating: " << _name << "\n";
    flag ++;

    if (flag > 25 && GetChildCount() > 0) {
      RemoveChild(&GetChildByIndex(0));
    }
  }

  void FixedUpdate() final {
    // std::cout << "fixed updating: " << _name << "\n";
  }

  ~Sample() {
    std::cout << "destroyed: " << _name << "\n";
  }
};

class Sample2 : public Node {
public:
  Sample2(const std::string &name) : Node(name) {
    std::cout << "created: " << _name << "\n";
  }

  ~Sample2() {
    std::cout << "destroyed: " << _name << "\n";
  }
};

int main() {
  App &app = App::Instance();
  app.Init(800, 800, "Sandbox #1");

  auto node = MakeNode<Sample>("Sample root");
  node->AddChild(MakeNode<Sample2>("Sample2 child"));

  SceneTree tree;
  tree.SetRoot(std::move(node));

  app.SetCurrentScene(std::move(tree));
  app.Run();
}