
#include "debug/engine/node/ast_debug.hpp"
#include "debug/engine/token/dump_tokens.hpp"
#include "engine/CompilationUnit.hpp"

#include "engine/lexer/lexer.hpp"
#include "engine/parser/parser.hpp"
#include "engine/resolver/Resolver.hpp"
#include "frontend/checker/TypeChecker.hpp"

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

    debug::engine::dump_tokens(comp_unit.tokens);

    parser.parse_program();

    for (auto &node : comp_unit.ast.get_nodes()) {
      degub.debug_node(node, true);
      resolver.resolve(node);
    }

    // for (auto &node : comp_unit.ast.get_nodes()) { checker.check(node); }
  }
};