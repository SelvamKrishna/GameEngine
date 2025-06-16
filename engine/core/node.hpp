#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <vector>

class SceneTree;

class Node {
public:
  enum class ErrorCode : uint8_t {
    Success,
    NullChild,
    ChildWithNameExists,
  };

  enum class State : uint8_t {
    Uninitialized,
    Active,
    Disabled,
  };

protected:
  friend SceneTree;

  using ChildrenArray = std::vector<std::unique_ptr<Node>>;

  std::string _name;
  Node *_parent = nullptr;
  std::unique_ptr<ChildrenArray> _children;
  State _state = State::Uninitialized;

private:
  virtual void _Init() {}
  virtual void _Update() {}
  virtual void _FixedUpdate() {}

  ErrorCode _UpdateTree();
  ErrorCode _FixedUpdateTree();

public:
  explicit Node(const std::string &name);
  virtual ~Node() = default;

  Node(const Node &) = delete;
  Node(Node &&) noexcept = default;
  Node &operator=(const Node &) = delete;
  Node &operator=(Node &&) noexcept = default;

  void Free() noexcept;

  ErrorCode AddChild(Node *child) noexcept;
  ErrorCode RemoveChild(Node *child) noexcept;

  [[nodiscard]] Node &ChildByIndex(size_t index);
  [[nodiscard]] Node &ChildByName(std::string_view name);

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] NodeT *ChildByType() {
    for (auto &child : *_children) 
      if (NodeT *casted = dynamic_cast<NodeT *>(child.get()); casted) return casted;

    return nullptr;
  }

  [[nodiscard]] inline size_t ChildCount() const noexcept { return _children->size(); }
  [[nodiscard]] inline const Node *Parent() const noexcept { return _parent; }
  [[nodiscard]] inline std::string_view Name() const noexcept { return _name; }

  [[nodiscard]] inline const ChildrenArray *Children() const noexcept {
    return _children ? _children.get() : nullptr;
  }
};
