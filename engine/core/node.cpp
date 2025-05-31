#include "node.hpp"
#include "component.hpp"
#include <algorithm>
#include <format>

Node::Node(const std::string &name) : _parent(nullptr), _name(name) {}

void Node::AddChild(std::unique_ptr<Node> child) {
  for (const auto &currentChild : _children) {
    if (currentChild->_name == child->_name) [[unlikely]] {
      throw NodeError(
        std::format( "Child with name '{}' already exists.", child->_name)
      );
    }
  }

  child->_parent = this;
  child->Init();
  _children.emplace_back(std::move(child));
}

void Node::RemoveChild(Node *child) noexcept {
  auto it = std::ranges::find_if(
    _children,
    [child](const std::unique_ptr<Node> &ptr) {
      return ptr.get() == child; 
    }
  );

  if (it != _children.end()) [[likely]] {
    (*it)->_parent = nullptr;
    _children.erase(it);
  }
}

Node &Node::GetChildByIndex(size_t index) {
  if (index >= _children.size()) [[unlikely]]
    throw std::out_of_range("Child index out of range");

  return *_children[index];
}

Node &Node::GetChildByName(std::string_view name) {
  for (const auto &child : _children) {
    if (child->_name == name) return *child;
  }

  throw NodeError( std::format("Child with name '{}' not found.", name));
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
  if (index >= _components.size()) [[unlikely]]
    throw std::out_of_range("Component index out of range");

  return *_components[index];
}

void Node::UpdateTree() {
  Update();
  
  for (auto &component : _components) {
    if (component == nullptr) [[unlikely]] 
      throw NodeError("Null component in UpdateTree");

    component->Update();
  }

  for (auto &child : _children) {
    if (child == nullptr) [[unlikely]]
      throw NodeError("Null child in UpdateTree"); 

    child->UpdateTree();
  }
}

void Node::FixedUpdateTree() {
  FixedUpdate();
  for (auto &component : _components) {
    if (component == nullptr) [[unlikely]]
      throw NodeError("Null component null in FixedUpdateTree");

    component->FixedUpdate();
  }

  for (auto &child : _children) {
    if (child == nullptr) [[unlikely]]
      throw NodeError("Null child in FixedUpdateTree");
    
    child->FixedUpdateTree();
  }
}

void Node::Free() noexcept {
  _parent = nullptr;

  for (auto &child : _children) child->Free();

  _children.clear();
  _components.clear();
}