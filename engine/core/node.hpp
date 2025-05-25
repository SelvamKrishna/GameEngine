#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Node {
protected:
  Node *_parent = nullptr;
  std::vector<std::unique_ptr<Node>> _children;
  std::string _name;

public:
  Node(const std::string &name);
  virtual ~Node() = default;

  static std::unique_ptr<Node> Create(const std::string &name);

  void ResizeChildrenList(size_t newSize);

  void AddChild(std::unique_ptr<Node> child);
  void RemoveChild(Node *child);

  Node &GetChild(Node *child);
  Node &GetChild(size_t index);

  virtual void Init() {}
  virtual void Update(const float deltaTime) {}
  virtual void FixedUpdate() {}

  void UpdateTree(const float deltaTime);
  void FixedUpdateTree();

  inline const std::string &GetName() const { return _name; }
  void Free();
};
