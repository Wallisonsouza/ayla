#pragma once

#include "core/memory/Arena.hpp"
#include "core/token/Location.hpp"
#include "frontend/ast/AstNode.hpp"
#include <functional>
#include <vector>

class Ast {
public:
  Ast() = default;

  template <typename T, typename... Args> T *create_node(Args &&...args) {
    T *node = ast_arena.alloc<T>(std::forward<Args>(args)...);
    return node;
  }

  template <typename T, typename... Args> T *create_error_node(const SourceSlice &slice, Args &&...args) {
    T *node = ast_arena.alloc<T>(std::forward<Args>(args)...);

    node->kind = ayla::ast::NodeKind::Error;

    node->slice = slice;
    node->range = slice.range;
    return node;
  }

  void traverse(const std::function<void(ayla::ast::AstNode *)> &fn) const {
    for (auto *node : roots_) fn(node);
  }

  size_t size() const { return roots_.size(); }
  const std::vector<ayla::ast::AstNode *> &get_nodes() const { return roots_; }

  void add_root(ayla::ast::AstNode *node) { roots_.push_back(node); }

private:
  core::memory::Arena ast_arena;
  std::vector<ayla::ast::AstNode *> roots_;
};
