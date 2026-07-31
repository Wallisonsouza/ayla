#pragma once

#include "celestia/ast/AstNode.hpp"
#include "celestia/core/memory/Arena.hpp"

class Ast {
public:
  Ast() = default;

  template <typename T, typename... Args> T *create_node(Args &&...args) {
    T *node = ast_arena.alloc<T>(std::forward<Args>(args)...);
    return node;
  }

  void set_root(celestia::ast::AstNode *node) { root_ = node; }

  celestia::ast::AstNode *get_root() const { return root_; }

private:
  core::memory::Arena ast_arena;
  celestia::ast::AstNode *root_;
};
