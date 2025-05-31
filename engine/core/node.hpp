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

protected:
  Node *_parent = nullptr;
  std::string _name;
  std::vector<std::unique_ptr<Node>> _children;
  std::vector<std::unique_ptr<Component>> _components;

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

  void AddChild(std::unique_ptr<Node> child);
  void RemoveChild(Node *child) noexcept;

  [[nodiscard]] Node &GetChildByIndex(size_t index);
  [[nodiscard]] Node &GetChildByName(std::string_view name);

  [[nodiscard]] inline size_t GetChildCount() const noexcept {
    return _children.size();
  }

  void AddComponent(std::unique_ptr<Component> component);
  void RemoveComponent(Component *component) noexcept;
  [[nodiscard]] Component &GetComponentByIndex(size_t index);

  template <typename ComponentT>
  [[nodiscard]] ComponentT &GetComponent() const {
    for (const auto &component : _components) {
      if (auto casted = dynamic_cast<ComponentT *>(component.get())) return *casted;
    }

    throw std::invalid_argument("Component not available");
  }

  template <typename ComponentT>
  [[nodiscard]] bool HasComponent() const noexcept {
    for (const auto &component : _components) {
      if (dynamic_cast<ComponentT *>(component.get())) return true;
    }

    return false;
  }

  template <typename ComponentT>
  [[nodiscard]] std::vector<ComponentT *> GetComponentsByType() const noexcept {
    std::vector<ComponentT *> matches;
    for (const auto &component : _components) {
      if (auto casted = dynamic_cast<ComponentT *>(component.get())) matches.push_back(casted);
    }

    return matches;
  }

  [[nodiscard]] inline const Node *GetParent() const noexcept { return _parent; }
  [[nodiscard]] inline const std::string &GetName() const noexcept { return _name; }

  [[nodiscard]] inline const std::vector<std::unique_ptr<Node>> &
  GetChildren() const noexcept {
    return _children;
  }

  [[nodiscard]] inline const std::vector<std::unique_ptr<Component>> &
  GetComponents() const noexcept {
    return _components;
  }

  void Free() noexcept;
};
