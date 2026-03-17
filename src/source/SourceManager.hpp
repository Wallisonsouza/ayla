#pragma once

#include "ayla/source/source.hpp"
#include <memory>
#include <unordered_map>

class SourceManager {
  std::unordered_map<std::string, std::unique_ptr<ayla::source::Source>> sources;

public:
  ayla::source::Source &load(const std::string &path) {

    auto it = sources.find(path);
    if (it != sources.end()) return *it->second;

    auto src = std::make_unique<ayla::source::Source>(path);
    auto &ref = *src;

    sources[path] = std::move(src);
    return ref;
  }
};
