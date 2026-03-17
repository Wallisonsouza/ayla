#pragma once

#include "ayla/source/source_buffer.hpp"
#include "utils/TextLoader.hpp"
#include <string>
#include <utility>

namespace ayla::source {

struct Source {
  std::string path;
  SourceBuffer buffer;

  Source(std::string p) : path(std::move(p)), buffer(utils::TextLoader::load_file(path)) {}
};

} // namespace ayla::source
