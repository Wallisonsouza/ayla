#pragma once

#include <functional>
#include <unordered_map>

#include "celestia/core/visitor/Stage.hpp"

#include "celestia/ast/AstNode.hpp"
#include "celestia/core/visitor/NodeTraits.hpp"
#include "celestia/engine/CompilationUnit.hpp"

class AstStage : public Stage {

public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override { dispatch(unit.ast.get_root()); }

protected:
  void dispatch(const celestia::ast::AstNode *node) {
    auto it = handlers.find(node->kind);

    if (it != handlers.end()) it->second(node);
  }

  template <typename Node, typename Owner> void bind(void (Owner::*method)(const Node *)) {

    handlers[celestia::ast::NodeTraits<Node>::kind] = [this, method](const celestia::ast::AstNode *node) {
      auto *owner = static_cast<Owner *>(this);

      (owner->*method)(static_cast<const Node *>(node));
    };
  }

private:
  using Handler = std::function<void(const celestia::ast::AstNode *)>;

  std::unordered_map<celestia::ast::NodeKind, Handler> handlers;
};