#include "celestia/core/visitor/Stage.hpp"
#include "celestia/engine/CompilerEnvironment.hpp"
#include "celestia/syntax/parser/Parser.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"

class ParserStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    ParseContext context = ParseContext(unit, env);
    celestia::Parser parser(context);

    parser.run();
  };
};