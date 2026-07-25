#pragma once

#include "SourceBuffer.hpp"
#include "utils/TextLoader.hpp"

#include <filesystem>
#include <string>
#include <utility>

namespace core::source {

struct Source {
  std::string path;
  SourceBuffer buffer;

  explicit Source(std::string p) : path(std::move(p)), buffer(utils::TextLoader::load_file(path)) {}

  std::string filename() const { return std::filesystem::path(path).filename().string(); }

  std::string stem() const { return std::filesystem::path(path).stem().string(); }
};

} // namespace core::source