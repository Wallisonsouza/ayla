#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/ast/NodeKind.hpp"
#include "celestia/ast/NodeTraits.hpp"

#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

enum class DispatchResult { Handled, NotHandled };

template <typename ContextType, typename BaseNode = celestia::ast::Node> class AstDispatcher {
public:
  using HandlerFunc = void (*)(ContextType *, BaseNode *);

  AstDispatcher() = default;

  template <typename TargetNode, void (ContextType::*Method)(TargetNode *)> void bind() {
    constexpr auto kind = celestia::ast::NodeTraits<TargetNode>::kind;
    const size_t index = static_cast<size_t>(kind);

    if (index >= table.size()) { table.resize(index + 1, nullptr); }

    assert(table[index] == nullptr && "AstDispatcher: Handler already registered for this NodeKind");

    table[index] = [](ContextType *ctx, BaseNode *node) { (ctx->*Method)(static_cast<TargetNode *>(node)); };
  }

  template <typename TargetNode, void (ContextType::*Method)(const TargetNode *)> void bind() {
    constexpr auto kind = celestia::ast::NodeTraits<TargetNode>::kind;
    const size_t index = static_cast<size_t>(kind);

    if (index >= table.size()) { table.resize(index + 1, nullptr); }

    assert(table[index] == nullptr && "AstDispatcher: Handler already registered for this NodeKind");

    table[index] = [](ContextType *ctx, BaseNode *node) { (ctx->*Method)(static_cast<const TargetNode *>(node)); };
  }

  [[nodiscard]] DispatchResult dispatch(ContextType *ctx, BaseNode *node) const {
    assert(node != nullptr && "AstDispatcher: cannot dispatch null node");

    const size_t index = static_cast<size_t>(node->kind);

    if (index >= table.size() || table[index] == nullptr) { return DispatchResult::NotHandled; }

    table[index](ctx, node);
    return DispatchResult::Handled;
  }

  void dispatch_required(ContextType *ctx, BaseNode *node) const {
    if (dispatch(ctx, node) == DispatchResult::NotHandled) {
      throw std::runtime_error(std::string("AstDispatcher: no handler registered for NodeKind: ") + std::string(celestia::ast::node_kind_name(node->kind)));
    }
  }

  void reserve(size_t capacity) { table.reserve(capacity); }

private:
  std::vector<HandlerFunc> table;
};
