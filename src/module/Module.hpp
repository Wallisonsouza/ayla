#include "semantic/scope/Scope.hpp"
#include <string>

class Module {
public:
  std::string name;
  core::Scope scope;

  std::vector<Module *> imports;
};