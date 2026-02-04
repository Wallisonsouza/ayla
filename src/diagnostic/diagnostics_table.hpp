#pragma once
#include "diagnostic/diagnostic_code.hpp"
#include <unordered_map>

struct DiagnosticTemplate {
  const char *title;
  const char *message;
  const char *help;
};

static const std::unordered_map<DiagnosticCode, DiagnosticTemplate> DIAG_PT_BR = {

    {DiagnosticCode::UnexpectedToken, {"Erro de sintaxe", "Token inesperado", "Verifique se você digitou corretamente o token."}},

    {DiagnosticCode::ExpectedToken, {"Erro de sintaxe", "Esperado '{expected}', encontrado '{found}'", "Verifique se o token {expected} foi escrito corretamente."}},

    {DiagnosticCode::ExpectedIdentifier, {"Erro de sintaxe", "Esperado identificador '{expected}', encontrado '{found}'", "Declare um nome válido para a variável ou função."}},

    {DiagnosticCode::ExpectedType, {"Erro de tipo", "Esperado tipo '{expected}', encontrado '{found}'", "Declare um tipo válido. Exemplo: val x: i32;"}},

    {DiagnosticCode::ExpectedExpression, {"Erro de sintaxe", "Esperado expressão '{expected}'", "Forneça uma expressão válida. Exemplo: val x: i32 = 10;"}},

    {DiagnosticCode::ExpectedColon, {"Erro de sintaxe", "Esperado ':' após o identificador", "Use ':' para separar nome da variável e tipo. Exemplo: val x: i32;"}},

    {DiagnosticCode::ExpectedDoubleColon, {"Erro de sintaxe", "Esperado '::'", "Use '::' para acessar membros estáticos ou namespaces."}},

    {DiagnosticCode::UndeclaredSymbol, {"Erro de nome", "Símbolo '{found}' não declarado", "Declare o símbolo '{found}' antes de usá-lo. Exemplo: val {found}: i32;"}},

    {DiagnosticCode::NotCallable, {"Erro de tipo", "Tentativa de chamar algo não chamável", "Certifique-se de que a variável ou expressão é uma função."}},

    {DiagnosticCode::UnterminatedString, {"Erro de sintaxe", "String não terminada", "Verifique se você fechou todas as aspas da string."}},

    {DiagnosticCode::ModuleNotFound, {"Erro de semântica", "Módulo não encontrado", "Importe apenas módulos válidos existentes."}},

    {DiagnosticCode::RedeclaredIdentifier, {"Erro de semântica", "Identificador '{name}' já declarado neste escopo", "Renomeie a variável ou remova a declaração anterior para evitar conflito."}},

    {DiagnosticCode::BlockError, {"Erro de sintaxe", "Bloco inválido ou ausente", "Certifique-se de que o bloco contém pelo menos uma instrução."}},

    {DiagnosticCode::TypeMismatch, {"Erro de tipo", "Tipo incompatível", "Certifique-se de que os tipos das expressões são compatíveis."}},

    {DiagnosticCode::InvalidArguments, {"Erro de chamada de função", "Número ou tipo de argumentos inválido", "Verifique a assinatura da função e passe os argumentos corretos."}},

    // ===== IF =====
    {DiagnosticCode::ConditionMissing, {"Erro de sintaxe", "Condição do '{expected}' ausente", "Adicione uma expressão válida depois do '{expected}'. Exemplo: {expected} x > 0 { ... }"}},

    {DiagnosticCode::ConditionAssignment, {"Erro de sintaxe", "Atribuições não são permitidas na condição do '{expected}'", "Use uma expressão booleana. Exemplo: {expected} x > 0 { ... }"}},

    {DiagnosticCode::ThenBlockMissing,
     {"Erro de sintaxe", "Bloco '{block}' ausente ou vazio", "Adicione pelo menos uma instrução dentro do bloco '{block}'. Exemplo: {expected} cond { println(\"ok\") }"}},

    {DiagnosticCode::ElseBlockMissing, {"Erro de sintaxe", "Bloco '{block}' ausente ou inválido", "Adicione pelo menos uma instrução dentro do bloco '{block}'. Exemplo: else { println(\"ok\") }"}},
    
    {DiagnosticCode::UnknownType, {"Erro de tipo", "Tipo desconhecido", "A expressão possui tipo desconhecido. Verifique declarações e inferências de tipo."}},

    {DiagnosticCode::InvalidMemberAccess, {"Erro de tipo", "Acesso inválido a membro", "O tipo '{base_type}' não suporta acesso a membros. Exemplo: apenas objetos podem ter membros."}},

    {DiagnosticCode::MemberNotFound, {"Erro de nome", "Membro '{member}' não encontrado", "O objeto não possui o membro '{member}'. Verifique o nome ou a estrutura do objeto."}},

};
