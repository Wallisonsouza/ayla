#pragma once

#include <functional>
#include <unordered_map>

#include "core/visitor/Stage.hpp"

#include "ast/AstNode.hpp"
#include "core/visitor/NodeTraits.hpp"
#include "engine/CompilationUnit.hpp"

class AstStage : public Stage {

public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override { dispatch(unit.ast.get_root()); }

protected:
  void dispatch(const ayla::ast::AstNode *node) {
    auto it = handlers.find(node->kind);

    if (it != handlers.end()) it->second(node);
  }

  template <typename Node, typename Owner> void bind(void (Owner::*method)(const Node *)) {

    handlers[ayla::ast::NodeTraits<Node>::kind] = [this, method](const ayla::ast::AstNode *node) {
      auto *owner = static_cast<Owner *>(this);

      (owner->*method)(static_cast<const Node *>(node));
    };
  }

private:
  using Handler = std::function<void(const ayla::ast::AstNode *)>;

  std::unordered_map<ayla::ast::NodeKind, Handler> handlers;
};