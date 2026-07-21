#include "AstDumper.hpp"
#include <format>


void AstDumper::debug_number_literal(const ayla::ast::node::NumberLiteralNode *node) { debug_header(std::format("Number({})", node->value)); }

void AstDumper::debug_string_literal(const ayla::ast::node::StringLiteralNode *node) { out << "String: \"" << node->value << "\"\n"; }

void AstDumper::debug_bool_literal(const ayla::ast::node::BoolLiteralNode *node) { out << "Boolean: " << (node->value ? "true" : "false") << "\n"; }

void AstDumper::debug_null_literal(const ayla::ast::node::NullLiteralNode *node) {
  (void)node;
  out << "NullLiteral\n";
}

void AstDumper::debug_array_literal(const ayla::ast::node::ArrayLiteralNode *node) {
  out << "ArrayLiteral\n";

  for (size_t i = 0; i < node->elements.size(); ++i) {
    bool is_last = (i + 1 == node->elements.size());
    debug_node(node->elements[i], is_last);
  }
}


void AstDumper::debug_object_literal(const ayla::ast::node::ObjectLiteralNode *node) {
  out << "Object\n";

  if (!node->fields.empty()) {
    for (size_t i = 0; i < node->fields.size(); ++i) {
      bool is_last = (i + 1 == node->fields.size());
      debug_node(node->fields[i], is_last);
    }
  }
}