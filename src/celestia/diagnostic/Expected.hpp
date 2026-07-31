#pragma once

namespace diagnostic {

enum class ExpectedKind {
  Token,

  Identifier,

  Expression,

  Pattern,

  Type,

  Declaration
};


} // namespace diagnostic