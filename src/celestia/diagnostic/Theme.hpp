#pragma once

#include "celestia/debug/console/color.hpp"

namespace diagnostic::theme {

using C = debug::Color;

inline const auto ErrorLabel = C::BrightRed;
inline const auto ErrorText = C::Red;

inline const auto Arrow = C::DarkRed;

inline const auto LineInfo = C::BrightBlue;

inline const auto LineNumber = C::BrightBlack;
inline const auto Separator = C::BrightBlack;

inline const auto Source = C::White;

inline const auto Underline = C::DarkRed;

inline const auto Caret = C::BrightRed;

inline const auto Help = C(255, 215, 120);

} // namespace diagnostic::theme