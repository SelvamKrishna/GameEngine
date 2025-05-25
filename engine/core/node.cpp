#include "node.hpp"
#include <algorithm>
#include <stdexcept>

Node::Node(const std::string &name) : _name(name) {}

std::unique_ptr<Node> Node::Create(const std::string &name) {
  return std::make_unique<Node>(name);
}

void Node::ResizeChildrenList(size_t newSize) {
  if (newSize > _children.size()) _children.resize(newSize);
}

void Node::AddChild(std::unique_ptr<Node> child) {
  child->_parent = this;
  child->Init();
  _children.emplace_back(std::move(child));
}

void Node::RemoveChild(Node *child) {
  auto it = std::find_if(_children.begin(), _children.end(), 
    [child](const std::unique_ptr<Node> &ptr) {
      return ptr.get() == child;
    }
  );

  if (it != _children.end()) {
    (*it)->_parent = nullptr;
    _children.erase(it);
  }
}

Node &Node::GetChild(Node *child) {
  auto it = std::find_if(_children.begin(), _children.end(), 
    [child](const std::unique_ptr<Node> &ptr) {
      return ptr.get() == child;
    }
  );

  if (it == _children.end())
    throw std::runtime_error("Child node not found");

  return *it->get();
}

Node &Node::GetChild(size_t index) {
  if (index >= _children.size())
    throw std::out_of_range("Child index out of range");

  return *_children[index];
}

void Node::UpdateTree(const float deltaTime) {
  Update(deltaTime);
  for (auto &child : _children) child->UpdateTree(deltaTime);
}

void Node::FixedUpdateTree() {
  FixedUpdate();
  for (auto &child : _children) child->FixedUpdateTree();
}

void Node::Free() {
  _parent = nullptr;
  for (auto &child : _children) child->Free();
  _children.clear();
}