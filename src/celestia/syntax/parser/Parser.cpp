#include "Parser.hpp"

#include "ParserContext.hpp"

#include "DeclarationParser.hpp"
#include "ExpressionParser.hpp"
#include "NameParser.hpp"
#include "PatternParser.hpp"
#include "StatementParser.hpp"
#include "TypeParser.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/syntax/parser/ParserUtil.hpp"
#include <vector>

namespace celestia {
Parser::Parser(ParseContext &context) : context(context) {
  declaration_parser = std::make_unique<DeclarationParser>(context, *this);
  expression_parser = std::make_unique<ExpressionParser>(context, *this);
  statement_parser = std::make_unique<StatementParser>(context, *this);
  pattern_parser = std::make_unique<PatternParser>(context, *this);
  type_parser = std::make_unique<TypeParser>(context, *this);
  name_parser = std::make_unique<NameParser>(context, *this);
}

Parser::~Parser() = default;

void Parser::run() {
  auto *module = declarations().parse_module_declaration();

  if (!module) { module = context.get_ast().create_node<celestia::ast::ModuleDeclaration>(nullptr); }

  auto *script = context.get_ast().create_node<celestia::ast::BlockStatement>();

  auto &tokens = context.tokens();

  while (!tokens.is_end()) {

    if (auto *decl = declarations().parse_declaration()) {
      module->declarations.push_back(decl);
      continue;
    }

    if (auto *stmt = statements().parse_statement()) {
      script->statements.push_back(stmt);
      continue;
    }

    tokens.advance();
  }

  context.unit.module = module;
  context.unit.script = script;

  context.get_ast().set_root(module);
}

} // namespace celestia
