#pragma once

#include <algorithm>
#include <string>
#include <vector>

class Node {
protected:
  Node *_parent = nullptr;
  std::vector<Node *> _children;
  std::string _name;

public:
  Node(const std::string &name = "Node") : _name(name) {}

  virtual ~Node() {
    for (Node *child : _children) delete child;
  }

  void AddChild(Node *child) {
    child->_parent = this;
    _children.push_back(child);
    child->Start();
  }

  void RemoveChild(Node *child) {
    _children.erase(
      std::remove(_children.begin(), _children.end(), child),
      _children.end()
    );

    delete child;
  }

  virtual void Start() {}
  virtual void Update(const float delta) {}
  virtual void FixedUpdate(const float delta) {}

  void UpdateTree(const float delta) {
    Update(delta);
    for (auto child : _children) child->UpdateTree(delta);
  }

  void FixedUpdateTree(const float delta) {
    FixedUpdate(delta);
    for (auto child : _children) child->FixedUpdateTree(delta);
  }

  const std::string &GetName() const { return _name; }
};
