#pragma once
#include "diagnostic/diagnostic_code.hpp"
#include <unordered_map>

struct DiagnosticTemplate {
  const char *title;
  const char *message;
  const char *help;
};

static const std::unordered_map<DiagnosticCode, DiagnosticTemplate> DIAG_PT_BR = {

    // ===== IF =====
    {DiagnosticCode::ConditionMissing,
     {"Erro de sintaxe", "Condição do '{expected}' ausente",
      "Adicione uma expressão válida depois do '{expected}'. Exemplo: "
      "{expected} x > 0 { ... }"}},

    {DiagnosticCode::ConditionAssignment, {"Erro de sintaxe", "Atribuições não são permitidas na condição do '{expected}'", "Use uma expressão booleana. Exemplo: {expected} x > 0 { ... }"}},

    {DiagnosticCode::ThenBlockMissing,
     {"Erro de sintaxe", "Bloco '{block}' ausente ou vazio",
      "Adicione pelo menos uma instrução dentro do bloco '{block}'. "
      "Exemplo: {expected} cond { println(\"ok\") }"}},

    {DiagnosticCode::ElseBlockMissing,
     {"Erro de sintaxe", "Bloco '{block}' ausente ou inválido",
      "Adicione pelo menos uma instrução dentro do bloco '{block}'. "
      "Exemplo: else { println(\"ok\") }"}},

    // ===== VARIABLE DECLARATION =====
    {DiagnosticCode::ExpectedIdentifier, {"Erro de sintaxe", "Esperado '{expected}' found '{found}'", "Declare um nome válido"}},

    {DiagnosticCode::ExpectedColon,
     {"Erro de sintaxe", "Esperado '{expected}' após o identificador",
      "Use '{expected}' para separar o nome da variável e o tipo. Exemplo: "
      "val x{expected} i32;"}},

    {DiagnosticCode::ExpectedType, {"Erro de tipo", "{expected} {found}", "Declare um tipo válido. Exemplo: val x: i32;"}},

    {DiagnosticCode::ExpectedExpression, {"Erro de sintaxe", "Esperado '{expected}'", "Forneça uma expressão válida. Exemplo: val x: i32 = 10;"}},

    {DiagnosticCode::ExpectedToken, {"Erro de sintaxe", "Esperado '{expected}', encontrado '{found}'", "Verifique se o token {expected} foi escrito corretamente."}},
    {DiagnosticCode::ModuleNotFound,
     {"Erro de semântica", "Modulo não encontrado",
      "Importe somente modulos validos "
      "conflito."}},
    // symbol
    {DiagnosticCode::RedeclaredIdentifier,
     {"Erro de semântica", "Identificador '{name}' já declarado neste escopo",
      "Renomeie a variável ou remova a declaração anterior para evitar "
      "conflito."}},
    {DiagnosticCode::UndeclaredSymbol,
     {"Erro de nome", "Esperado '{expected}', encontrado '{found}'",
      "Declare o símbolo '{found}' antes de usá-lo. Exemplo: val {found}: "
      "i32;"}}

};
