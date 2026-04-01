#pragma once

#include "ayla-compilation/unit.hpp"
#include "diagnostic/diagnostic_context.hpp"
#include <string>

std::string render_value(const DiagnosticValue &v, const ayla::compilation::Unit &unit);

std::string apply_template(const std::string &tmpl, const DiagnosticContext &ctx, const ayla::compilation::Unit &unit);

void print(const Diagnostic &diag, const ayla::compilation::Unit &unit);