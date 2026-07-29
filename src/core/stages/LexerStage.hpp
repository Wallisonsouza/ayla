#include "core/visitor/Stage.hpp"
#include "engine/CompilationUnit.hpp"
#include "syntax/lexer/Lexer.hpp"

class LexerStage : public Stage {

public:
  void run(CompilationUnit &unit) override {

    Lexer lexer(unit);
    lexer.tokenize();
  }
};
