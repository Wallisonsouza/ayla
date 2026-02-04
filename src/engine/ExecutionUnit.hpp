
#include "debug/engine/node/ast_debug.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/lexer/lexer.hpp"
#include "engine/parser/parser.hpp"
#include "engine/resolver/Resolver.hpp"

struct ExecutionUnit {
  CompilationUnit &comp_unit;
  Lexer lexer;
  Parser parser;
  Resolver resolver;

public:
  ExecutionUnit(CompilationUnit &unit) : comp_unit(unit), lexer(unit), parser(unit), resolver(unit, &unit.context.root_scope) {}

  void execute() {
    lexer.generate_tokens();

    parser.parse_program();

    ASTDebug debug;
    debug.dump_ast(comp_unit.ast);
    resolver.resolve_ast();
  }
};