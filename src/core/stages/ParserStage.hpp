#include "core/visitor/Stage.hpp"
#include "syntax/parser/Parser.hpp"
#include "syntax/parser/ParserContext.hpp"

class ParserStage : public Stage {
  void run(CompilationUnit &unit) override {

    ParseContext context = ParseContext(unit);
    Parser parser(context);

    parser.run();
  };
};