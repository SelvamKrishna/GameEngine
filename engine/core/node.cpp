#include "node.hpp"
#include <algorithm>
#include <exception>
#include <cassert>

Node::Node(const std::string &name) : _name(name) {}

Node::ErrorCode Node::_UpdateTree() {
  if (_state != State::Active) return ErrorCode::Success;

  _Update();

  if (!_children) return ErrorCode::Success;

  ErrorCode error;
  for (auto &child : *_children) {
    if (!child) return ErrorCode::NullChild;

    error = child->_UpdateTree(); 
    if (error != ErrorCode::Success) return error;
  }

  return ErrorCode::Success;
}

Node::ErrorCode Node::_FixedUpdateTree() {
  if (_state != State::Active) return ErrorCode::Success;

  _FixedUpdate();

  if (!_children) return ErrorCode::Success;

  ErrorCode error;
  for (auto &child : *_children) {
    if (!child) return ErrorCode::NullChild;

    if (child->_state != State::Active) continue;

    error = child->_FixedUpdateTree(); 
    if (error != ErrorCode::Success) return error;
  }

  return ErrorCode::Success;
}

void Node::Free() noexcept {
  _parent = nullptr;
  _children.reset();
  _state = State::Uninitialized;
}

Node::ErrorCode Node::AddChild(Node *child) noexcept {
  if (!child) return ErrorCode::NullChild;

  if (!_children) _children = std::make_unique<ChildrenArray>();

  auto &arr = *_children;

  bool childExists = std::ranges::any_of(
    arr, 
    [&child](const auto &existing) {
      return existing && existing->_name == child->_name;
    }
  );

  if (childExists) return ErrorCode::ChildWithNameExists;

  child->_parent = this;
  child->_Init();

  arr.emplace_back(child);
  return ErrorCode::Success;
}

Node::ErrorCode Node::RemoveChild(Node *child) noexcept {
  if (!child || !_children) return ErrorCode::NullChild;

  auto &arr = *_children;

  auto it = std::remove_if(
    arr.begin(), arr.end(),
    [child](const std::unique_ptr<Node> &ptr) { return ptr.get() == child; }
  );

  if (it == arr.end()) return ErrorCode::NullChild;

  (*it)->_parent = nullptr;
  arr.erase(it, arr.end());

  if (arr.empty()) _children.reset();

  return ErrorCode::Success;
}

Node &Node::ChildByIndex(size_t index) {
  assert(_children && "Children array is not initialized");
  assert(index < _children->size() && "Index out of bounds");
  return *(*_children)[index];
}

Node &Node::ChildByName(std::string_view name) {
  assert(_children && "Children array is not initialized");

  for (const auto &child : *_children)
    if (child->_name == name) return *child;

  assert(false && "Child with given name not found");
  std::terminate();
}