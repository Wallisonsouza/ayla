
#include "debug/ast/AstDumper.hpp"
#include "debug/lexer/TokenDumper.hpp"
#include "engine/Pass.hpp"
#include "semantic/checker/TypeChecker.hpp"
#include "semantic/resolver/Resolver.hpp"
#include "syntax/lexer/lexer.hpp"
#include "syntax/parser/Parser.hpp"
#include "syntax/parser/ParserContext.hpp"
#include <iostream>

class LexerPass : public Pass {
  void run(CompilationUnit &unit) override {

    Lexer lex(unit);

    lex.tokenize();
  };
};

class ResolvePass : public Pass {
  void run(CompilationUnit &unit) override {

    auto scope = unit.scope_manager.create_scope(nullptr);
    Resolver resolver(unit, scope);

    for (auto node : unit.ast.get_nodes()) { resolver.resolve(node); }
  };
};

class CheckPass : public Pass {
  void run(CompilationUnit &unit) override {

    ayla::TypeChecker checker(unit);

    for (auto node : unit.ast.get_nodes()) { checker.check(node); }
  };
};

class TokenDumpPass : public Pass {

  void run(CompilationUnit &unit) override {

    debug::lexer::TokenDumper dumper;

    std::cout << dumper.dump(unit.tokens);
  };
};

class ParsePass : public Pass {
  void run(CompilationUnit &unit) override {

    ParseContext context = ParseContext(unit);
    Parser parser(context);

    parser.run();
  };
};

class AstDumpPass : public Pass {

  void run(CompilationUnit &unit) override {
    AstDumper debug;
    debug.dump_ast(unit.ast);
  };
};
