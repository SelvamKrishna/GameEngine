#include "node.hpp"
#include "debug.hpp"
#include <algorithm>
#include <memory>

#ifdef PR_DEBUG
#include <format>
#endif

Node::Node(const std::string &name)
  : _name(name) {}

void Node::Free() noexcept {
  _parent = nullptr;
  _children.reset();
}

void Node::AddChild(Node *child) {
  PR_ASSERT_NODE(child != nullptr, "Cannot add null child");

  if (!_children) _children = std::make_unique<Children>();

  PR_ASSERT_NODE(
    !std::ranges::any_of(*_children, [&](const auto &existing) {
      return existing->_name == child->_name;
    }),
    std::format("Child with name '{}' already exists.", child->_name)
  );

  child->_parent = this;
  child->Init();
  _children->emplace_back(std::unique_ptr<Node>(child));
}

void Node::RemoveChild(Node *child) noexcept {
  if (!child || !_children) return;

  auto &vec = *_children;
  auto it = std::remove_if(vec.begin(), vec.end(),
    [child](const std::unique_ptr<Node> &ptr) {
      return ptr.get() == child;
    }
  );

  if (it != vec.end()) {
    (*it)->_parent = nullptr;
    vec.erase(it, vec.end());
  }

  if (_children->empty()) _children.reset();
}

Node &Node::GetChildByIndex(size_t index) {
  PR_ASSERT_NODE(_children && index < _children->size(), "Child index out of range");
  return *(*_children)[index];
}

Node &Node::GetChildByName(std::string_view name) {
  PR_ASSERT_NODE(_children, "This node has no children");

  for (const auto &child : *_children) {
    if (child->_name == name) return *child;
  }

  PR_ASSERT_NODE(false, "Child with given name not found");
  static Node dummy("unused");
  return dummy;
}

void Node::UpdateTree() {
  Update();

  if (!_children) return;

  for (auto &child : *_children) {
    PR_ASSERT_NODE(child != nullptr, "Null child found during UpdateTree");
    child->UpdateTree();
  }
}

void Node::FixedUpdateTree() {
  FixedUpdate();

  if (!_children) return; 

  for (auto &child : *_children) {
    PR_ASSERT_NODE(child != nullptr, "Null child found during FixedUpdateTree");
    child->FixedUpdateTree();
  }
}