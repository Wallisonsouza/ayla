#pragma once

#include "core/node/BinaryOp.hpp"
#include "core/node/Type.hpp"
#include <functional>
#include <unordered_map>

namespace core::table {

class OperatorTable {
public:
  using FoldCallback = std::function<ayla::ast::ExpressionNode *(ayla::ast::ExpressionNode *, ayla::ast::ExpressionNode *)>;

  void register_operation(ayla::ast::BinaryOperation op, ayla::ast::TypeNode *left_type, ayla::ast::TypeNode *right_type, FoldCallback cb) {
    Key key{op, left_type, right_type};
    table_[key] = cb;
  }

  FoldCallback *get(ayla::ast::BinaryOperation op, ayla::ast::TypeNode *left_type, ayla::ast::TypeNode *right_type) {
    Key key{op, left_type, right_type};
    auto it = table_.find(key);
    if (it != table_.end()) return &it->second;
    return nullptr;
  }

private:
  struct Key {
    ayla::ast::BinaryOperation op;
    ast::TypeNode *left;
    ast::TypeNode *right;

    bool operator==(const Key &other) const { return op == other.op && left == other.left && right == other.right; }
  };

  struct KeyHash {
    std::size_t operator()(const Key &k) const {
      auto h1 = std::hash<int>()(static_cast<int>(k.op));
      auto h2 = std::hash<void *>()(k.left);
      auto h3 = std::hash<void *>()(k.right);
      return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
  };

  std::unordered_map<Key, FoldCallback, KeyHash> table_;
};

} // namespace core::table
