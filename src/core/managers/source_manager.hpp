#pragma once
#include "core/memory/Arena.hpp"
#include "core/source/Source.hpp"

class SourceManager {
  core::memory::Arena arena;

public:
  core::source::Source *create_source(const std::string &path) { return arena.alloc<core::source::Source>(path); }
};