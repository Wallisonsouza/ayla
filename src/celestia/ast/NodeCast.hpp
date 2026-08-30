#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/ast/NodeTraits.hpp"

#include <cassert>

namespace celestia::ast {

template <typename T> bool is(const Node *node) {

  if (!node) return false;

  return node->kind == NodeTraits<T>::kind;
}

template <typename T> T *as(Node *node) {

  assert(node);
  assert(is<T>(node));

  return static_cast<T *>(node);
}

template <typename T> const T *as(const Node *node) {

  assert(node);
  assert(is<T>(node));

  return static_cast<const T *>(node);
}

template <typename T> T *try_as(Node *node) {

  if (!is<T>(node)) return nullptr;

  return static_cast<T *>(node);
}

template <typename T> const T *try_as(const Node *node) {

  if (!is<T>(node)) return nullptr;

  return static_cast<const T *>(node);
}

} // namespace celestia::ast