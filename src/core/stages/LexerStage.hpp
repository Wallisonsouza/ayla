#include "core/visitor/Stage.hpp"
#include "engine/CompilationUnit.hpp"
#include "syntax/lexer/Lexer.hpp"
#include "syntax/lexer/LexerContext.hpp"

class LexerStage : public Stage {
public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {
    
    LexerContext ctx(env.language, unit.source, unit.tokens);

    Lexer lexer(ctx);

    lexer.tokenize();
  }
};