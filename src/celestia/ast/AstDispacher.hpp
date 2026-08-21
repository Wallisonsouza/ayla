#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/ast/NodeKind.hpp"
#include "celestia/ast/NodeKindName.hpp"
#include "celestia/core/visitor/NodeTraits.hpp"

#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

enum class DispatchResult { Handled, NotHandled };

class AstDispatcher {
public:
  template <typename Owner> explicit AstDispatcher(Owner *owner) : owner(owner) {

    if (!owner) throw std::invalid_argument("AstDispatcher: owner cannot be null");
  }

  template <typename Node, typename Owner> void bind(void (Owner::*method)(Node *)) {

    const auto kind = celestia::ast::NodeTraits<Node>::kind;

    auto handler = [this, method](celestia::ast::Node *node) { (static_cast<Owner *>(owner)->*method)(static_cast<Node *>(node)); };

    auto [it, inserted] = handlers.emplace(kind, std::move(handler));

    if (!inserted) { throw std::runtime_error(std::string("AstDispatcher: handler already registered for NodeKind: ") + std::string(celestia::ast::node_kind_name(kind))); }
  }

  DispatchResult dispatch(celestia::ast::Node *node) {

    if (!node) throw std::invalid_argument("AstDispatcher: cannot dispatch null node");

    auto it = handlers.find(node->kind);

    if (it == handlers.end()) return DispatchResult::NotHandled;

    it->second(node);

    return DispatchResult::Handled;
  }

  void dispatch_required(celestia::ast::Node *node) {

    const auto result = dispatch(node);

    if (result == DispatchResult::NotHandled) { throw std::runtime_error(std::string("AstDispatcher: no handler registered for NodeKind: ") + std::string(celestia::ast::node_kind_name(node->kind))); }
  }

private:
  void *owner;

  std::unordered_map<celestia::ast::NodeKind, std::function<void(celestia::ast::Node *)>> handlers;
};