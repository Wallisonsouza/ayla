#pragma once
#include <cstdint>
namespace ayla::structural::token {
enum class TokenKind : uint8_t {
  STATIC,
  MUT,
  PUBLIC,
  PRIVATE,
  INVALID,
  COMMENT,

  EXTERN_KEYWORD,
  MODULE_KEYWORD,
  VALUE_KEYWORD,
  CONST_KEYWORD,
  FUNCTION_KEYWORD,
  IMPORT_KEYWORD,
  IF_KEYWORD,     // Representa a palavra-chave 'if'.
  ELSE_KEYWORD,   // Representa a palavra-chave 'else'.
  RETURN_KEYWORD, // Representa a palavra-chave 'return'.
  WHILE_KEYWORD,

  OPEN_BRACKET,
  CLOSE_BRACKET,
  COMMA,        // Representa a vírgula ','.d
  DOUBLE_QUOTE, // Representa uma aspa dupla '"'.
  SINGLE_QUOTE, // Representa uma aspa simples '\''.
  COLON,        // Representa o caractere ':'.
  ARROW,
  PLUS,   // Representa o operador de adição '+'.
  MINUS,  // Representa o operador de subtração '-'.
  STAR,   // Representa o operador de multiplicação '*'.
  SLASH,  // Representa o operador de divisão '/'.
  ASSIGN, // Representa o operador de atribuição '='.
  EQUAL,  // Representa o operador de igualdade '=='.
  NOT_EQUAL,
  Ternary,    // Representa o operador ternário '?'.
  LESS,       // Representa o operador '<'.
  LESS_EQUAL, // Representa o operador '>'.
  GREATER,
  GREATER_EQUAL,

  OPEN_PAREN,  // Representa o parêntese esquerdo '('.
  Space,       // Representa um espaço em branco.
  CLOSE_PAREN, // Representa o parêntese direito ')'.

  OPEN_BRACE,  // Representa a chave esquerda '{'.
  CLOSE_BRACE, // Representa a chave direita '}'.
  SEMI_COLON,  // Representa o ponto e vírgula ';'.
  DOT,
  Alias,          // Representa um alias (como 'type alias' em algumas linguagens).
  IDENTIFIER,     // Representa nomes de variáveis, funções ou outros
                  // identificadores.
  NUMBER_LITERAL, // Representa um literal numérico, como 42 ou 3.14.
  STRING_LITERAL, // Representa um literal de string, como "texto".
  NullLiteral,    // Representa o valor nulo 'null'.
  CharLiteral,    // Representa um literal de caractere, como 'a'.
  BoolLiteral,    // Representa um literal booleano: true ou false.
  EndOfFile,      // Representa o fim do arquivo, usado para indicar que não há mais
  NEW_LINE,
  Type, // mais tokens a serem lidos.
  // tokens.
};
}