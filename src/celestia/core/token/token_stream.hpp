#pragma once

#include "celestia/core/memory/Arena.hpp"
#include "celestia/core/token/Token.hpp"

#include <functional>
#include <vector>

namespace core::token {

class TokenStream {

public:
  TokenStream() = default;

  // ============================================================
  // Token creation
  // ============================================================

  template <typename T, typename... Args> T *create_token(Args &&...args) {
    T *tok = arena_.alloc<T>(std::forward<Args>(args)...);
    tokens_.push_back(tok);
    return tok;
  }

  // ============================================================
  // Inspection
  // ============================================================

  void for_each(const std::function<void(const Token &)> &fn) const {
    for (auto *token : tokens_) {
      if (token) fn(*token);
    }
  }

  TokenKind kind() const noexcept { return kind_at(0); }

  TokenKind lookahead_kind(size_t distance) const noexcept { return kind_at(distance); }

  bool check(TokenKind expected, size_t distance = 0) const noexcept { return kind_at(distance) == expected; }

  bool is_end() const noexcept { return pos_ >= tokens_.size(); }

  bool has(size_t distance = 0) const noexcept { return pos_ + distance < tokens_.size(); }

  size_t current_pos() const noexcept { return pos_; }

  // ============================================================
  // Token access
  // ============================================================

  Token *current() const noexcept { return has() ? tokens_[pos_] : nullptr; }

  Token *previous() const noexcept { return pos_ == 0 ? nullptr : tokens_[pos_ - 1]; }

  // ============================================================
  // Trivia
  // ============================================================

  bool is_trivia() const noexcept { return kind() == TokenKind::NEW_LINE; }

  void skip_trivia() noexcept {
    while (!is_end() && is_trivia()) consume();
  }

  // ============================================================
  // Consumption
  // ============================================================

  Token *consume() noexcept {
    if (is_end()) return nullptr;

    last_token_ = tokens_[pos_];
    return tokens_[pos_++];
  }

  Token *advance() noexcept { return consume(); }

  void advance(size_t count) noexcept {
    while (count-- && !is_end()) consume();
  }

  Token *match(TokenKind expected) {
    if (!check(expected)) return nullptr;

    return consume();
  }

  bool consume_if(TokenKind expected) {
    if (!check(expected)) return false;

    consume();
    return true;
  }

  Token *expect(TokenKind expected) {
    if (!check(expected)) return nullptr;

    return consume();
  }

  // ============================================================
  // Checkpoints
  // ============================================================

  void add_checkpoint() noexcept { checkpoint_stack_.push_back(pos_); }

  void rollback_checkpoint() noexcept {
    if (checkpoint_stack_.empty()) return;

    pos_ = checkpoint_stack_.back();
    checkpoint_stack_.pop_back();
  }

  void discard_checkpoint() noexcept {
    if (checkpoint_stack_.empty()) return;

    checkpoint_stack_.pop_back();
  }

  // ============================================================
  // Source location
  // ============================================================

  const SourceSlice &last_slice() const noexcept {
    static SourceSlice empty{};

    return last_token_ ? last_token_->slice : empty;
  }

  const SourceSlice &diagnostic_slice() const noexcept {
    if (auto *token = current()) { return token->slice; }

    return last_slice();
  }
  const SourceSlice &current_slice() const noexcept {
    static SourceSlice empty{};

    if (auto *token = current()) return token->slice;

    return empty;
  }

  // ============================================================
  // Misc
  // ============================================================

  size_t size() const noexcept { return tokens_.size(); }

  void traverse(const std::function<void(Token *)> &fn) const {
    for (auto *token : tokens_) fn(token);
  }

  void reset(size_t position) noexcept { pos_ = std::min(position, tokens_.size()); }

private:
  TokenKind kind_at(size_t distance) const noexcept {
    if (!has(distance)) return TokenKind::EndOfFile;

    auto *token = tokens_[pos_ + distance];

    return token ? token->kind() : TokenKind::EndOfFile;
  }

private:
  core::memory::Arena arena_;
  std::vector<Token *> tokens_;

  size_t pos_ = 0;
  std::vector<size_t> checkpoint_stack_;

  Token *last_token_ = nullptr;
};

} // namespace core::token