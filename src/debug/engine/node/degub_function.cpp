#include "debug/engine/node/ast_debug.hpp"

void ASTDebug::debug_function_declaration(const parser::node::FunctionDeclarationNode *node) {

  debug_header("FunctionDeclaration");

  if (node->identifier) { debug_node(node->identifier, false); }

  if (!node->params.empty()) { debug_labeled_childrens(node->params, "Args", node->return_type == nullptr && node->body == nullptr); }

  if (node->return_type) { debug_labeled("ReturnType", node->return_type, node->body == nullptr); }

  if (node->body) { debug_node(node->body, true); }
}

// void ASTDebug::debug_funtion_parameter(const ayla::ast::FunctionParameterNode *node) {

//   debug_header("FunctionParameter");

//   if (node->identifier) { debug_labeled("Identifier", node->identifier, false); }
//   if (node->type) { debug_labeled("Type", node->type, false); }
//   if (node->value) { debug_labeled("Value", node->value, true); }
// }

void ASTDebug::debug_function_call(const ayla::ast::node::CallExpressionNode *node) {
  out << "FunctionCall\n";

  if (node->callee) {
    bool callee_is_last = node->arguments.empty();
    debug_labeled("Callee", node->callee, callee_is_last);
  }

  if (!node->arguments.empty()) { debug_labeled_childrens(node->arguments, "Args", true); }
}
