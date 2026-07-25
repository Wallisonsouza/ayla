#pragma once

#include "ast/AstNode.hpp"
#include "core/memory/Arena.hpp"
#include "core/token/Location.hpp"

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

  void set_root(ayla::ast::AstNode *node) { root_ = node; }

  ayla::ast::AstNode *get_root() const { return root_; }

private:
  core::memory::Arena ast_arena;
  ayla::ast::AstNode *root_;
};
