#pragma once
#include "ayla-structural/ayla-token/token.hpp"
#include "core/memory/Arena.hpp"
#include <functional>
#include <vector>

namespace ayla::structural::token {

class TokenStream {
public:
  TokenStream() = default;

  // -----------------------------
  // Criação
  // -----------------------------
  template <typename T, typename... Args> T *create_token(Args &&...args) {
    T *tok = arena_.alloc<T>(std::forward<Args>(args)...);
    tokens_.push_back(tok);
    return tok;
  }

  void traverse(const std::function<void(Token *)> &fn) const {
    for (auto *tok : tokens_) fn(tok);
  }

  size_t size() const { return tokens_.size(); }

  Token *operator[](size_t idx) const { return tokens_[idx]; }

  const std::vector<Token *> &get_tokens() const { return tokens_; }

public:
  size_t pos_ = 0;
  std::vector<size_t> checkpoint_stack_;

  // -----------------------------
  // Acesso
  // -----------------------------
  inline bool is_end() const noexcept { return pos_ >= tokens_.size(); }

  inline bool has(size_t offset = 0) const noexcept { return pos_ + offset < tokens_.size(); }

  inline size_t current_pos() const noexcept { return pos_; }

  inline Token *current() const noexcept { return has() ? tokens_[pos_] : nullptr; }

  inline Token *peek(size_t offset = 0) const noexcept { return has(offset) ? tokens_[pos_ + offset] : nullptr; }

  inline Token *previous() const noexcept { return pos_ == 0 ? nullptr : tokens_[pos_ - 1]; }

  // -----------------------------
  // Check helpers
  // -----------------------------
  inline bool check(TokenKind k, size_t offset = 0) const noexcept {
    auto *tok = peek(offset);
    return tok && tok->descriptor && tok->descriptor->kind == k;
  }

  inline bool peek(TokenKind k, size_t offset = 0) const noexcept { return check(k, offset); }

  // -----------------------------
  // Consumo
  // -----------------------------
  inline Token *consume() noexcept {
    if (is_end()) return nullptr;

    last_token_ = tokens_[pos_];
    return tokens_[pos_++];
  }

  inline Token *advance() noexcept {
    return consume(); // alias semântico
  }

  inline void advance(size_t count) noexcept {
    while (count-- && !is_end()) consume();
  }

  // -----------------------------
  // Match / Expect
  // -----------------------------
  Token *match(TokenKind kind) {
    if (!check(kind)) return nullptr;
    return consume();
  }

  bool consume_if(TokenKind kind) {
    if (!check(kind)) return false;
    consume();
    return true;
  }

  Token *expect(TokenKind kind) {
    if (check(kind)) return consume();

    // erro simples — parser decide como reportar
    return consume();
  }

  // -----------------------------
  // Checkpoints
  // -----------------------------
  inline void add_checkpoint() noexcept { checkpoint_stack_.push_back(pos_); }

  inline void rollback_checkpoint() noexcept {
    if (!checkpoint_stack_.empty()) {
      pos_ = checkpoint_stack_.back();
      checkpoint_stack_.pop_back();
    }
  }

  inline void discard_checkpoint() noexcept {
    if (!checkpoint_stack_.empty()) checkpoint_stack_.pop_back();
  }

  // -----------------------------
  // Localização
  // -----------------------------
  inline const ayla::source::SourceSlice &last_slice() const noexcept {
    static ayla::source::SourceSlice empty{};
    return last_token_ ? last_token_->slice : empty;
  }

  inline const ayla::source::SourceSlice &peek_slice(size_t offset = 0) const noexcept {
    static ayla::source::SourceSlice empty{};
    if (auto *tok = peek(offset)) return tok->slice;
    return empty;
  }

  inline const ayla::source::SourceSlice slice_of(const Token *tok) const noexcept {
    static ayla::source::SourceSlice empty{};
    return tok ? tok->slice : empty;
  }

  inline void reset(size_t p) noexcept { pos_ = (p <= tokens_.size()) ? p : tokens_.size(); }

private:
  core::memory::Arena arena_;
  std::vector<Token *> tokens_;
  Token *last_token_ = nullptr;
};

} // namespace ayla::structural::token
