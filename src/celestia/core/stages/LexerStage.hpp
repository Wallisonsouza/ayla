#include "celestia/core/visitor/Stage.hpp"
#include "celestia/engine/CompilationUnit.hpp"
#include "celestia/syntax/lexer/Lexer.hpp"
#include "celestia/syntax/lexer/LexerContext.hpp"

class LexerStage : public Stage {
public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {
    
    LexerContext ctx(env.language, unit.source, unit.tokens);

    Lexer lexer(ctx);

    lexer.tokenize();
  }
};