#include "node.hpp"
#include "component.hpp"
#include <algorithm>

#ifdef PR_DEBUG
#include <format>
#endif

Node::Node(const std::string &name) : _parent(nullptr), _name(name) {}

void Node::AddChild(std::unique_ptr<Node> child) {
#ifdef PR_DEBUG
  const auto duplicate = std::ranges::any_of(
    _children, 
    [&](const std::unique_ptr<Node> &existing) {
      return existing->_name == child->_name;
    }
  );

  if (duplicate) [[unlikely]]
    throw NodeError(std::format("Child with name '{}' already exists.", child->_name));
#endif

  child->_parent = this;
  child->Init();
  _children.emplace_back(std::move(child));
}

void Node::RemoveChild(Node *child) noexcept {
  auto it = std::ranges::find_if(
    _children,
    [child](const std::unique_ptr<Node> &ptr) { return ptr.get() == child; }
  );

  if (it != _children.end()) [[likely]] {
    (*it)->_parent = nullptr;
    _children.erase(it);
  }
}

Node &Node::GetChildByIndex(size_t index) {
#ifdef PR_DEBUG
  if (index >= _children.size()) [[unlikely]] 
    throw std::out_of_range("Child index out of range");
#endif
  return *_children[index];
}

Node &Node::GetChildByName(std::string_view name) {
  for (const auto &child : _children) {
    if (child->_name == name) return *child;
  }

#ifdef PR_DEBUG
  throw NodeError(std::format("Child with name '{}' not found.", name));
#endif

  return *_children.front();
}

void Node::AddComponent(std::unique_ptr<Component> component) {
  component->_owner = this;
  _components.emplace_back(std::move(component));
}

void Node::RemoveComponent(Component *component) noexcept {
  auto it = std::ranges::find_if(
    _components, 
    [component](const std::unique_ptr<Component> &ptr) {
      return ptr.get() == component;
    }
  );

  if (it != _components.end()) [[likely]] {
    (*it)->_owner = nullptr;
    _components.erase(it);
  }
}

Component &Node::GetComponentByIndex(size_t index) {
#ifdef PR_DEBUG
  if (index >= _components.size()) [[unlikely]]
    throw std::out_of_range("Component index out of range");
#endif

  return *_components[index];
}

void Node::UpdateTree() {
  Update();

  for (auto &component : _components) {
#ifdef PR_DEBUG
    if (!component) [[unlikely]]
      throw NodeError("Null component found during UpdateTree");
#endif
    component->Update();
  }

  for (auto &child : _children) {
#ifdef PR_DEBUG
    if (!child) [[unlikely]]
      throw NodeError("Null child found during UpdateTree");
#endif
    child->UpdateTree();
  }
}

void Node::FixedUpdateTree() {
  FixedUpdate();

  for (auto &component : _components) {
#ifdef PR_DEBUG
    if (!component) [[unlikely]]
      throw NodeError("Null component found during FixedUpdateTree");
#endif
    component->FixedUpdate();
  }

  for (auto &child : _children) {
#ifdef PR_DEBUG
    if (!child) [[unlikely]]
      throw NodeError("Null child found during FixedUpdateTree");
#endif
    child->FixedUpdateTree();
  }
}

void Node::Free() noexcept {
  _parent = nullptr;

  for (auto &child : _children) child->Free();

  _children.clear();
  _components.clear();
}