#include "debug/engine/node/ast_debug.hpp"
#include "engine/Pass.hpp"
#include "syntax/lexer/lexer.hpp"
#include "syntax/parser/parser.hpp"


class LexerPass: public Pass {
    void run(CompilationUnit &unit) override {

        Lexer lex(unit);

        lex.tokenize();
    };
};


class ParsePass: public Pass {
    void run(CompilationUnit &unit) override {

        Parser parser(unit);

        parser.generate();
    };
};


class DebugPass: public Pass {

    ASTDebug debug;

    void run(CompilationUnit &unit) override {

        debug.dump_ast(unit.ast);
      
    };
};
