#pragma once

#include <memory>
#include <string>

enum class ModuleSourceType { Native, Script };

class IModuleDescriptor {
public:
  virtual ~IModuleDescriptor() = default;
};

struct ModuleSource {

  ModuleSourceType type;

  std::string name;

  std::shared_ptr<IModuleDescriptor> descriptor;
};