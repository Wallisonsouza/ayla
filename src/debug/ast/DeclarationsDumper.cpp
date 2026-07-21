#include "AstDumper.hpp"

void AstDumper::debug_variable_declaration(const ayla::ast::node::VariableDeclarationNode *node) {

  out << "VariableDeclaration\n";

  std::vector<LabeledChild> children;

  if (node->pattern) children.push_back({"Pattern", node->pattern});

  // if (node->i) children.push_back({"Type", node->i});

  if (node->initializer) children.push_back({"Initializer", node->initializer});

  for (size_t i = 0; i < children.size(); ++i) {

    bool is_last = (i + 1 == children.size());

    debug_labeled(children[i].label, children[i].node, is_last);
  }
}

void AstDumper::debug_function_declaration(const ayla::ast::node::FunctionDeclarationNode *node) {

  debug_header("FunctionDeclaration");

  std::vector<LabeledChild> children;

  if (node->name) children.push_back({"Name: ", node->name});

  if (node->body) children.push_back({"Body: ", node->body});

  if (!node->parameters.empty()) { debug_labeled_childrens(node->parameters, "Args: ", false); }

  for (size_t i = 0; i < children.size(); ++i) {
    bool is_last = (i + 1 == children.size());
    debug_labeled(children[i].label, children[i].node, is_last);
  }

  if (!node->parameters.empty()) { debug_labeled_childrens(node->parameters, "Args: ", node->return_type == nullptr && node->body == nullptr); }

  if (node->return_type) { debug_labeled("ReturnType", node->return_type, node->body == nullptr); }
}

void AstDumper::debug_module_declaration(const ayla::ast::node::ModuleDeclarationNode *node) {
  out << "Module\n";

  for (size_t i = 0; i < node->name->parts.size(); ++i) { debug_node(node->name->parts[i], i == node->name->parts.size() - 1); }

  for (size_t i = 0; i < node->body.size(); ++i) { debug_node(node->body[i], i == node->body.size() - 1); }
}
