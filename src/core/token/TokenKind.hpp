#pragma once
#include <cstdint>

enum class TokenKind : uint8_t {
  STATIC,
  MUT,
  PUBLIC,
  PRIVATE,
  INVALID,
  COMMENT,

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
  Arrow,
  Plus,        // Representa o operador de adição '+'.
  Minus,       // Representa o operador de subtração '-'.
  Star,        // Representa o operador de multiplicação '*'.
  Slash,       // Representa o operador de divisão '/'.
  Assign,      // Representa o operador de atribuição '='.
  Equals,      // Representa o operador de igualdade '=='.
  Ternary,     // Representa o operador ternário '?'.
  LessThan,    // Representa o operador '<'.
  GreaterThan, // Representa o operador '>'.

  OPEN_PAREN,  // Representa o parêntese esquerdo '('.
  Space,       // Representa um espaço em branco.
  CLOSE_PAREN, // Representa o parêntese direito ')'.

  OPEN_BRACE,  // Representa a chave esquerda '{'.
  CLOSE_BRACE, // Representa a chave direita '}'.
  SEMI_COLON,  // Representa o ponto e vírgula ';'.
  Dot,
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
