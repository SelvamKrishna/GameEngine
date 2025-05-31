#pragma once

#include <string>

class Node;

class Component {
private:
  friend class Node;
  
  Node* _owner = nullptr;

protected:
  std::string _name;

private:
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