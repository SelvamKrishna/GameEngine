#pragma once

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class SceneTree;

class NodeError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

class Node {
private:
  friend SceneTree;

  using Children = std::vector<std::unique_ptr<Node>>;

  Node *_parent = nullptr;
  std::string _name;
  std::unique_ptr<Children> _children;

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

  void AddChild(Node *child);
  void RemoveChild(Node *child) noexcept;

  [[nodiscard]] Node &GetChildByIndex(size_t index);
  [[nodiscard]] Node &GetChildByName(std::string_view name);

  [[nodiscard]] inline size_t GetChildCount() const noexcept { return _children->size(); }
  [[nodiscard]] inline const Node *GetParent() const noexcept { return _parent; }
  [[nodiscard]] inline std::string_view GetName() const noexcept { return _name; }

  [[nodiscard]] inline const Children*
  GetChildren() const noexcept { return _children.get(); }
};
