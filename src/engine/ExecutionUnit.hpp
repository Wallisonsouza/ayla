
#include "debug/engine/node/ast_debug.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/checker/TypeChecker.hpp"
#include "engine/lexer/lexer.hpp"
#include "engine/parser/parser.hpp"
#include "engine/resolver/Resolver.hpp"

struct ExecutionUnit {
  CompilationUnit &comp_unit;
  Lexer lexer;
  Parser parser;
  Resolver resolver;
  // TypeChecker checker;

public:
  ExecutionUnit(CompilationUnit &unit) : comp_unit(unit), lexer(unit), parser(unit), resolver(unit, &unit.context.root_scope) {}

  void execute() {

    lexer.generate_tokens();

    ASTDebug degub;

    parser.parse_program();

    for (auto &node : comp_unit.ast.get_nodes()) { resolver.resolve(node); }
  }
};