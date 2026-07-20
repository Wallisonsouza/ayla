// #include "core/token/TokenKind.hpp"
// #include "syntax/parser/Parser.hpp"
// #include <cstdint>
// #include <unordered_map>

// inline bool has_flag(RecoverBoundary flags, RecoverBoundary test) { return (static_cast<uint32_t>(flags) & static_cast<uint32_t>(test)) != 0; }

// static const std::unordered_map<TokenGroup, RecoverBoundary> group_boundaries = {
//     {TokenGroup::Keyword, RecoverBoundary::Statement | RecoverBoundary::Function | RecoverBoundary::Variable},
//     {TokenGroup::Punctuation, RecoverBoundary::Statement | RecoverBoundary::Variable},

// };

// static const std::unordered_map<TokenKind, RecoverBoundary> token_boundaries = {
//     {TokenKind::SEMI_COLON, RecoverBoundary::Statement},
//     {TokenKind::NEW_LINE, RecoverBoundary::Statement},
//     {TokenKind::CLOSE_BRACE, RecoverBoundary::Statement | RecoverBoundary::Function | RecoverBoundary::Variable},
//     {TokenKind::OPEN_BRACE, RecoverBoundary::Function},
//     {TokenKind::COLON, RecoverBoundary::Function},
// };

// void Parser::recover_until(RecoverBoundary boundaries) {
//   while (!unit.tokens.is_end()) {
//     auto *tok = unit.tokens.peek();
//     if (!tok || !tok->descriptor) {
//       unit.tokens.advance();
//       continue;
//     }

//     auto *desc = tok->descriptor;
//     bool stop = false;

//     auto it_group = group_boundaries.find(desc->group);
//     if (it_group != group_boundaries.end() && has_flag(boundaries, it_group->second)) { stop = true; }

//     auto it_token = token_boundaries.find(desc->kind);
//     if (it_token != token_boundaries.end() && has_flag(boundaries, it_token->second)) { stop = true; }

//     if (stop) return;

//     unit.tokens.advance();
//   }
// }
