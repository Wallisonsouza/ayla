#pragma once

#include <functional>
#include <unordered_map>

#include "celestia/ast/NodeKindName.hpp"
#include "celestia/core/visitor/Stage.hpp"

#include "celestia/ast/Node.hpp"
#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/core/visitor/NodeTraits.hpp"

class AstStage : public Stage {

public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {
    if (auto *root = unit.module) { dispatch(root); }
  }

protected:
  void dispatch(const celestia::ast::Node *node) {

    if (!node) { throw std::runtime_error("Dispatcher: node nulo"); }

    auto it = handlers.find(node->kind);


    auto view = celestia::ast::node_kind_name(node->kind);

    if (it == handlers.end()) { throw std::runtime_error("Dispatcher: nenhum handler para NodeKind " + std::string(view)); }

    it->second(node);
  }

  template <typename Node, typename Owner> void bind(void (Owner::*method)(const Node *)) {

    handlers[celestia::ast::NodeTraits<Node>::kind] = [this, method](const celestia::ast::Node *node) {
      auto *owner = static_cast<Owner *>(this);

      (owner->*method)(static_cast<const Node *>(node));
    };
  }

private:
  using Handler = std::function<void(const celestia::ast::Node *)>;

  std::unordered_map<celestia::ast::NodeKind, Handler> handlers;
};