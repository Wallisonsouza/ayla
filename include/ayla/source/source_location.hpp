#pragma once

#include "ayla/source/source_span.hpp"

#include <cstddef>

struct Location {
  size_t offset;
  size_t line;
  size_t column;
};

struct SourceRange {
  Location begin;
  Location end;
};

struct SourceSlice {
  SourceRange range;
  ayla::source::SourceSpan span;
};

inline SourceSlice operator+(const SourceSlice &a, const SourceSlice &b) {
  SourceSlice result;
  result.range.begin = a.range.begin;
  result.range.end = b.range.end;
  result.span.begin = a.span.begin;
  result.span.end = b.span.end;
  return result;
}