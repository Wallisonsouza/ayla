#pragma once
#include "core/memory/Arena.hpp"
#include "core/node/Node.hpp"
#include <functional>
#include <vector>

class AST {
public:
  AST() = default;

  template <typename T, typename... Args> T *create_node(Args &&...args) {
    T *node = ast_arena.alloc<T>(std::forward<Args>(args)...);
    return node;
  }

  template <typename T, typename... Args> T *create_error_node(const ayla::source::SourceSlice &slice, Args &&...args) {
    T *node = ast_arena.alloc<T>(std::forward<Args>(args)...);

    node->kind = core::ast::NodeKind::Error;

    node->slice = slice;
    node->range = slice.range;
    return node;
  }

  void traverse(const std::function<void(core::ast::ASTNode *)> &fn) const {
    for (auto *node : roots_) fn(node);
  }

  size_t size() const { return roots_.size(); }
  const std::vector<core::ast::ASTNode *> &get_nodes() const { return roots_; }

  void add_root(core::ast::ASTNode *node) { roots_.push_back(node); }

private:
  core::memory::Arena ast_arena;
  std::vector<core::ast::ASTNode *> roots_;
};
