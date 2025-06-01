#include "component.hpp"
#include <cstring>

#ifdef PR_DEBUG
#include <stdexcept>
#endif

Component::Component(const std::string_view &name) 
  : _owner(nullptr), _name(name) {}

ComponentContainer::ComponentContainer(Node *owner) : _owner(owner) {
#ifdef PR_DEBUG 
  if (owner == nullptr) throw std::invalid_argument("Owner can't be null");
#endif
}

void ComponentContainer::Remove(Component *component) noexcept {
  auto it = std::ranges::find_if(
    _componentBuffer, 
    [component](const std::unique_ptr<Component> &ptr) {
      return ptr.get() == component;
    }
  );

  if (it != _componentBuffer.end()) [[likely]] {
    (*it)->_owner = nullptr;
    _componentBuffer.erase(it);
  }
}

Component &ComponentContainer::GetByIndex(size_t index) {
#ifdef PR_DEBUG
  if (index >= _componentBuffer.size()) [[unlikely]]
    throw std::out_of_range("Component index out of range");
#endif

  return *_componentBuffer[index];
}

void ComponentContainer::UpdateAll() {
  for (auto &component : _componentBuffer) {
#ifdef PR_DEBUG
    if (!component) [[unlikely]]
      throw ComponentError("Null component found during UpdateTree");
#endif
    component->Update();
  }
}

void ComponentContainer::FixedUpdateAll() {
  for (auto &component : _componentBuffer) {
#ifdef PR_DEBUG
    if (!component) [[unlikely]]
      throw ComponentError("Null component found during FixedUpdateTree");
#endif
    component->FixedUpdate();
  }
}