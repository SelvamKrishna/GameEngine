#pragma once

#include "component.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

class SceneTree;

class NodeError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

class Node {
private:
  friend SceneTree;

  Node *_parent = nullptr;
  std::string _name;
  std::vector<std::unique_ptr<Node>> _children;
  ComponentContainer _components;

private:
  virtual void Init() {}
  virtual void Update() {}
  virtual void FixedUpdate() {}

  void UpdateTree();
  void FixedUpdateTree();

public:
  explicit Node(const std::string &name);
  virtual ~Node() = default;

  Node(const Node &) = delete;
  Node(Node &&) noexcept = default;
  Node &operator=(const Node &) = delete;
  Node &operator=(Node &&) noexcept = default;

  void Free() noexcept;

  void AddChild(std::unique_ptr<Node> child);
  void RemoveChild(Node *child) noexcept;

  [[nodiscard]] Node &GetChildByIndex(size_t index);
  [[nodiscard]] Node &GetChildByName(std::string_view name);
  [[nodiscard]] inline size_t GetChildCount() const noexcept { return _children.size(); }
  
  [[nodiscard]] inline const Node *GetParent() const noexcept { return _parent; }
  [[nodiscard]] inline const std::string &GetName() const noexcept { return _name; }
  [[nodiscard]] inline ComponentContainer &Components() noexcept { return _components; }

  [[nodiscard]] inline const std::vector<std::unique_ptr<Node>> &
  GetChildren() const noexcept { return _children; }
};
