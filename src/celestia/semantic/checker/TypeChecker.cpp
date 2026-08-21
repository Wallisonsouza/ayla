#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {
TypeChecker::TypeChecker(ResolverContext &context) : context(context), dispatcher(this) {
  bind_literals();
  // bind_expressions();
  // bind_statements();
  // bind_declarations();
  // bind_types();
}

void TypeChecker::bind_literals() {

  dispatcher.bind<ast::NumberLiteralNode>(&TypeChecker::number_literal);

  dispatcher.bind<ast::StringLiteralNode>(&TypeChecker::string_literal);

  dispatcher.bind<ast::BoolLiteralNode>(&TypeChecker::boolean_literal);

  dispatcher.bind<ast::ArrayLiteralNode>(&TypeChecker::array_literal);
}

void TypeChecker::check(ast::Node *node) {

  if (!node) return;

  if (dispatcher.dispatch(node) == DispatchResult::NotHandled) { std::cerr << "Checker: no handler for NodeKind: " << celestia::ast::node_kind_name(node->kind) << '\n'; }
}
} // namespace celestia::semantic