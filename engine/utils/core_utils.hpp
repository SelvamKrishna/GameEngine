#pragma once

#include "../core/component.hpp"
#include "../core/node.hpp"
#include <memory>
#include <type_traits>
#include <utility>

template <typename NodeT, typename... Args>
requires std::is_base_of_v<Node, NodeT>
[[nodiscard]] std::unique_ptr<NodeT> MakeNode(Args &&...args) {
  return std::make_unique<NodeT>(std::forward<Args>(args)...);
}

template <typename ComponentT, typename... Args>
requires std::is_base_of_v<Component, ComponentT>
[[nodiscard]] std::unique_ptr<ComponentT> MakeComponent(Args &&...args) {
  return std::make_unique<ComponentT>(std::forward<Args>(args)...);
}