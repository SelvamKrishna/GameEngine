#include "component.hpp"

Component::Component(const std::string &name) noexcept
  : _owner(nullptr)
  , _name(name)
{}