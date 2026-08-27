#pragma once

#include "Declaration.hpp"

#include "celestia/ast/names/IdentifierNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/types/TypeNode.hpp"

#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"

namespace celestia::ast {

struct FunctionDeclaration : NamedDeclaration {

  std::vector<PatternNode *> parameters;

  TypeNode *return_type;

  BlockStatement *body;

  FunctionDeclaration(IdentifierNode *name = nullptr,
                      std::vector<IdentifierNode *> generic_parameters = {},
                      std::vector<PatternNode *> parameters = {},
                      TypeNode *return_type = nullptr,
                      BlockStatement *body = nullptr,
                      DeclarationSpecifiers specifiers = {})
      : NamedDeclaration(NodeKind::FunctionDeclaration, name, specifiers, std::move(generic_parameters)), parameters(std::move(parameters)), return_type(return_type), body(body) {}
};

} // namespace celestia::ast