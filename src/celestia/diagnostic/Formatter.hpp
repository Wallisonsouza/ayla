#pragma once

#include "celestia/diagnostic/Diagnostic.hpp"

#include <string>

namespace diagnostic {

class Formatter {

public:

    std::string format(const std::string& message, const Diagnostic& diagnostic) {

        std::string result = message;

        for (const auto& argument : diagnostic.arguments) {

            std::string key = argument_name(argument.kind);

            replace(
                result,
                "{" + key + "}",
                format_value(argument.value)
            );
        }

        return result;
    }


private:

    std::string argument_name(DiagnosticArgumentKind kind) {

        switch (kind) {

        case DiagnosticArgumentKind::Expected:
            return "expected";

        case DiagnosticArgumentKind::Found:
            return "found";

        case DiagnosticArgumentKind::Previous:
            return "previous";

        // case DiagnosticArgumentKind::Actual:
        //     return "actual";

        default:
            return "unknown";
        }
    }


    std::string format_value(const DiagnosticValue& value) {

        return std::visit([](auto&& arg) -> std::string {

            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, const Token*>) {
                return arg->descriptor->text;
            }

            else if constexpr (std::is_same_v<T, TokenKind>) {
              return"";
                // return token_kind_name(arg);
            }

            else if constexpr (std::is_same_v<T, ExpectedKind>) {
                   return"";
                // return expected_kind_name(arg);
            }

            else if constexpr (std::is_same_v<T, std::string>) {
                return arg;
            }

            else {
                return "<unknown>";
            }

        }, value);
    }


    void replace(
        std::string& text,
        const std::string& from,
        const std::string& to)
    {
        size_t pos = 0;

        while ((pos = text.find(from, pos)) != std::string::npos) {
            text.replace(pos, from.size(), to);
            pos += to.size();
        }
    }
};

}