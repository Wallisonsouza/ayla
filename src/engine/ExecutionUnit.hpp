
#include "ayla-semantic/ayla-checker/TypeChecker.hpp"
#include "ayla-semantic/ayla-resolver/Resolver.hpp"
#include "ayla-syntax/ayla-lexer/lexer.hpp"
#include "ayla-syntax/ayla-parser/parser.hpp"
#include "debug/engine/node/ast_debug.hpp"
#include "engine/CompilationUnit.hpp"

struct ExecutionUnit {
  CompilationUnit &comp_unit;
  Lexer lexer;
  Parser parser;
  Resolver resolver;
  TypeChecker checker;

public:
  ExecutionUnit(CompilationUnit &unit) : comp_unit(unit), lexer(unit), parser(unit), resolver(unit, &unit.context.root_scope), checker(unit) {}

  void execute() {

    lexer.generate_tokens();

    ASTDebug degub;

    parser.parse_program();

    for (auto &node : comp_unit.ast.get_nodes()) { resolver.resolve(node); }

    for (auto &node : comp_unit.ast.get_nodes()) { checker.check(node); }
  }
};