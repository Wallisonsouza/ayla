#include "diagnostic/formatter.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/Engine.hpp"
#include "language/argon_main.hpp"
#include "runtime/interpreter/executor.hpp"
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

int main() {

  auto context = ayla::language::create_context();
  auto engine = Engine(context);

  std::vector<std::string> scripts = {
      "/home/wallison/Documentos/git/ayla/src/stdlib/Convert.ayla",
      "/home/wallison/Documentos/git/ayla/src/stdlib/IO.ayla",
      "/home/wallison/Documentos/git/ayla/src/stdlib/console.ayla",
      "/home/wallison/Documentos/git/ayla/src/stdlib/glfw.ayla",
      "/home/wallison/Documentos/git/ayla/main.ay",
  };

  for (auto &path : scripts) {
    try {
      auto exec = engine.create_execution(path);
      exec->execute();

      for (auto &diag : exec->comp_unit.diagns.all()) { print(*diag, exec->comp_unit); }

      auto scope = std::make_shared<RuntimeScope>();
      Executor interpreter(scope);
      interpreter.execute_ast(exec->comp_unit);

    } catch (const std::exception &e) { std::cerr << "Erro ao executar " << path << ": " << e.what() << std::endl; }
  }

  return 0;
}
