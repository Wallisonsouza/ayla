#include "celestia/core/visitor/Stage.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/syntax/parser/Parser.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"

class ParserStage : public Stage {
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    celestia::syntax::ParseContext context = celestia::syntax::ParseContext(unit, env);
    celestia::syntax::Parser parser(context);

    parser.run();
  };
};