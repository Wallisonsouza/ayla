#pragma once
#include <memory>

class ParseContext;

class DeclarationParser;
class ExpressionParser;
class StatementParser;
class PatternParser;
class TypeParser;
class NameParser;

namespace celestia::ast {
class AstNode;
}

class Parser {

public:
  explicit Parser(ParseContext &context);
  ~Parser();

  void run();

  DeclarationParser &declarations() { return *declaration_parser; }

  ExpressionParser &expressions() { return *expression_parser; }

  StatementParser &statements() { return *statement_parser; }

  PatternParser &patterns() { return *pattern_parser; }

  TypeParser &types() { return *type_parser; }

  NameParser &names() { return *name_parser; }

private:
  ParseContext &context;

  std::unique_ptr<DeclarationParser> declaration_parser;

  std::unique_ptr<ExpressionParser> expression_parser;

  std::unique_ptr<StatementParser> statement_parser;

  std::unique_ptr<PatternParser> pattern_parser;

  std::unique_ptr<TypeParser> type_parser;

  std::unique_ptr<NameParser> name_parser;
};