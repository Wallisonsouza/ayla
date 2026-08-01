#pragma once

#include "celestia/ast/Node.hpp"
#include "celestia/ast/NodeKind.hpp"
#include "celestia/core/visitor/NodeTraits.hpp"

#include <functional>
#include <unordered_map>

class HandlerRegistry {
public:
  template <typename Owner> explicit HandlerRegistry(Owner *owner) : owner(owner) {}

  template <typename Node, typename Owner> void bind(void (Owner::*method)(Node *)) {
    handlers[celestia::ast::NodeTraits<Node>::kind] = [this, method](celestia::ast::Node *node) { (static_cast<Owner *>(owner)->*method)(static_cast<Node *>(node)); };
  }

  void dispatch(celestia::ast::Node *node) {
    auto it = handlers.find(node->kind);

    if (it != handlers.end()) it->second(node);
  }

private:
  void *owner;

  std::unordered_map<celestia::ast::NodeKind, std::function<void(celestia::ast::Node *)>> handlers;
};