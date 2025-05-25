#pragma once

#include <string>

class Node;

class Component {
private:
  Node* _owner = nullptr;
  std::string _name;

  friend class Node;

protected:
  virtual void Update() {}
  virtual void FixedUpdate() {}

public:
  explicit Component(const std::string& name) noexcept;
  virtual ~Component() = default;

  [[nodiscard]] inline Node& GetOwner() noexcept { return *_owner; }
  [[nodiscard]] inline const Node& GetOwner() const noexcept { return *_owner; }
  [[nodiscard]] inline const std::string& GetName() const noexcept { return _name; }
};
