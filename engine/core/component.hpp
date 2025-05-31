#pragma once

#include <string>

class Node;

class Component {
private:
  Node *_owner = nullptr;

  friend class Node;

protected:
  std::string _name;

protected:
  virtual void Update() {}
  virtual void FixedUpdate() {}

public:
  explicit Component(const std::string &name) noexcept 
    : _owner(nullptr), _name(name) {}

  virtual ~Component() = default;

  [[nodiscard]] Node &GetOwner() noexcept { return *_owner; }
  [[nodiscard]] const Node &GetOwner() const noexcept { return *_owner; }
  [[nodiscard]] const std::string &GetName() const noexcept { return _name; }
};