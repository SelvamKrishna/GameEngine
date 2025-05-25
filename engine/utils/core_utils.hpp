#pragma once

#include "../core/component.hpp"
#include "../core/node.hpp"
#include <memory>
#include <type_traits>
#include <utility>

template <typename NodeT, typename... Args>
[[nodiscard]] std::unique_ptr<NodeT> MakeNode(Args &&...args) {
  static_assert(std::is_base_of<Node, NodeT>::value, "NodeT must inherit from Node");
  return std::make_unique<NodeT>(std::forward<Args>(args)...);
}

template <typename ComponentT, typename... Args>
[[nodiscard]] std::unique_ptr<ComponentT> MakeComponent(Args &&...args) {
  static_assert(std::is_base_of<Component, ComponentT>::value, "ComponentT must inherit from Component");
  return std::make_unique<ComponentT>(std::forward<Args>(args)...);
}
