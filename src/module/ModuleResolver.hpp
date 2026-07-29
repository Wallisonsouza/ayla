#pragma once

#include "ModuleSource.hpp"

#include <filesystem>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

class ModuleResolver {

public:
  explicit ModuleResolver(std::vector<std::filesystem::path> paths = {}) : search_paths_(std::move(paths)) {}

  void register_native(std::string name) { native_modules_.insert(std::move(name)); }

  std::optional<ModuleSource> resolve(std::string_view name) const;

private:
  std::optional<std::filesystem::path> find_file(std::string_view name) const;

private:
  std::vector<std::filesystem::path> search_paths_;

  std::unordered_set<std::string> native_modules_;
};