#pragma once

#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

class Node;

class ComponentError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

class Component {
private:
  friend class Node;
  friend class ComponentContainer;

  Node *_owner = nullptr;

protected:
  std::string _name;

private:
  virtual void Update() {}
  virtual void FixedUpdate() {}

public:
  explicit Component(const std::string_view &name);
  virtual ~Component() = default;

  [[nodiscard]] Node &GetOwner() noexcept { return *_owner; }
  [[nodiscard]] const Node &GetOwner() const noexcept { return *_owner; }
  [[nodiscard]] const std::string &GetName() const noexcept { return _name; }
};

class ComponentContainer {
private:
  friend class Node;

  Node *_owner = nullptr;
  std::vector<std::unique_ptr<Component>> _componentBuffer;

private:
  ComponentContainer(Node *owner);
  ~ComponentContainer() = default;  

  void UpdateAll();
  void FixedUpdateAll();

public:
  template <typename ComponentT>
    requires std::is_base_of_v<Component, ComponentT>
  inline void Add(ComponentT *component) {
#ifdef PR_DEBUG
    if (!component) throw std::invalid_argument("Component can't be null");
#endif
    component->_owner = _owner;
    _componentBuffer.emplace_back(std::unique_ptr<ComponentT>(component));
  }
  
  void Remove(Component *component) noexcept;

  template <typename ComponentT> [[nodiscard]] bool Has() const noexcept {
    for (const std::unique_ptr<Component> &component : _componentBuffer) {
      if (dynamic_cast<ComponentT *>(component.get())) return true;
    }

    return false;
  }

  template <typename ComponentT> 
    requires std::is_base_of_v<Component, ComponentT>
  [[nodiscard]] ComponentT &Get() const {
    for (const auto &component : _componentBuffer) {
      if (auto casted = dynamic_cast<ComponentT *>(component.get())) return *casted;
    }

#ifdef PR_DEBUG
    throw std::invalid_argument("Component not available");
#endif
    return *_componentBuffer.front();
  }

  template <typename ComponentT>
    requires std::is_base_of_v<Component, ComponentT>
  [[nodiscard]] std::vector<ComponentT *> GetAllByType() const noexcept {
    std::vector<ComponentT *> matches;
    for (const auto &component : _componentBuffer) {
      if (auto casted = dynamic_cast<ComponentT *>(component.get())) 
        matches.push_back(casted);
    }

    return matches;
  }

  [[nodiscard]] Component &GetByIndex(size_t index);
  [[nodiscard]] inline size_t Count() const noexcept { return _componentBuffer.size(); }
};