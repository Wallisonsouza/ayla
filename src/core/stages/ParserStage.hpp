#include "core/visitor/Stage.hpp"
#include "engine/CompilerEnvironment.hpp"
#include "syntax/parser/Parser.hpp"
#include "syntax/parser/ParserContext.hpp"

class ParserStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    ParseContext context = ParseContext(unit, env);
    Parser parser(context);

    parser.run();
  };
};