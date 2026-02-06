#include "Resolver.hpp"
#include "frontend/ast/statements/VariableDeclarationNode.hpp"

void Resolver::resolve_variable_declaration(ayla::ast::node::VariableDeclarationNode *node){
    resolve_pattern(node->pattern);
}