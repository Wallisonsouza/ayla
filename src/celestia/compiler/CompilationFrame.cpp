#include "CompilationFrame.hpp"
#include "celestia/compiler/Compiler.hpp"

CompilationFrame& CompilationFrame::add_script(
    const std::string& path) {

  units_.push_back(compiler_.add_script(path));

  return *this;
}

void CompilationFrame::run() {
  for (auto* unit : units_) {
    pipeline_.run(compiler_.environment(), *unit);
  }
}