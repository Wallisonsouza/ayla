#pragma once

#include "core/module/module.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace core {

using ModuleId = size_t;

struct ModuleManager {
  std::vector<Module> modules;
  std::unordered_map<std::string, ModuleId> root_modules;

  ModuleId create_module(const std::string &name, ModuleId parent_id = SIZE_MAX) {
    ModuleId id = modules.size();
    modules.emplace_back(name, parent_id);
    if (parent_id == SIZE_MAX) {
      root_modules[name] = id;
    } else {
      modules[parent_id].children[name] = id;
    }
    return id;
  }

  ModuleId create_module_path(const std::vector<ayla::ast::node::IdentifierExpressionNode *> &path) {

    if (path.empty()) return SIZE_MAX;

    ModuleId current = SIZE_MAX;

    for (auto *id_node : path) {
      ModuleId next = SIZE_MAX;
      const std::string &name = id_node->name;

      if (current == SIZE_MAX) {
        // raiz
        auto it = root_modules.find(name);
        if (it != root_modules.end()) next = it->second;
      } else {
        // filhos
        auto &children = modules[current].children;
        auto it = children.find(name);
        if (it != children.end()) next = it->second;
      }

      if (next == SIZE_MAX) {

        next = modules.size();
        modules.emplace_back(name, current);
        if (current == SIZE_MAX)
          root_modules[name] = next;
        else
          modules[current].children[name] = next;
      }

      current = next;
    }

    return current;
  }

  Module *get(ModuleId id) { return &modules[id]; }

  ModuleId find_path(std::vector<ayla::ast::node::IdentifierExpressionNode *> &path, size_t &failed_index) {
    failed_index = SIZE_MAX;

    if (path.empty()) return SIZE_MAX;

    auto it = root_modules.find(path[0]->name);
    if (it == root_modules.end()) {
      failed_index = 0;
      return SIZE_MAX;
    }

    ModuleId current = it->second;
    for (size_t i = 1; i < path.size(); ++i) {
      auto child_it = modules[current].children.find(path[i]->name);
      if (child_it == modules[current].children.end()) {
        failed_index = i;
        return SIZE_MAX;
      }
      current = child_it->second;
    }

    return current;
  }

  ModuleId find_path(const std::vector<std::string> &path) {
    if (path.empty()) return SIZE_MAX;

    auto it = root_modules.find(path[0]);
    if (it == root_modules.end()) return SIZE_MAX;

    ModuleId current = it->second;
    for (size_t i = 1; i < path.size(); ++i) {
      auto child_it = modules[current].children.find(path[i]);
      if (child_it == modules[current].children.end()) return SIZE_MAX;
      current = child_it->second;
    }

    return current;
  }

  const std::vector<Module> &get_all() const { return modules; }
};

} // namespace core
