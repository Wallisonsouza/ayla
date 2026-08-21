#pragma once

#include "celestia/core/token/Token.hpp"

#include <string>
#include <utility>

enum class ParseStatus { Success, NoMatch, Error };

namespace celestia::syntax {

struct ParseError {
  Token *token;
  std::string message;
};

template <typename T> class ParseResult {
  ParseStatus status_;
  T value_;
  ParseError error_;

  ParseResult(ParseStatus status, T value, ParseError error) : status_(status), value_(std::move(value)), error_(std::move(error)) {}

public:
  static ParseResult ok(T value) { return ParseResult(ParseStatus::Success, std::move(value), {}); }

  static ParseResult fail(Token *token, std::string message) { return ParseResult(ParseStatus::Error, T{}, {token, std::move(message)}); }

  static ParseResult no_match() { return ParseResult(ParseStatus::NoMatch, T{}, {}); }

  bool is_ok() const { return status_ == ParseStatus::Success; }

  bool is_error() const { return status_ == ParseStatus::Error; }

  bool is_no_match() const { return status_ == ParseStatus::NoMatch; }

  T &value() { return value_; }

  const T &value() const { return value_; }

  const ParseError &error() const { return error_; }
};

} // namespace celestia::syntax