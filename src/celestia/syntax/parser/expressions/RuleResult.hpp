// #include "celestia/syntax/parser/ParserContext.hpp"

// enum class RuleStatus { NoMatch, Success, Error };

// template <typename T> struct RuleResult {
//   RuleStatus status;
//   T value;

//   static RuleResult success(T value) { return {RuleStatus::Success, value}; }

//   static RuleResult no_match() { return {RuleStatus::NoMatch, nullptr}; }

//   static RuleResult error() { return {RuleStatus::Error, nullptr}; }

//   bool is_no_match() const { return status == RuleStatus::NoMatch; }

//   bool is_success() const { return status == RuleStatus::Success; }

//   bool is_error() const { return status == RuleStatus::Error; }
// };

// template <typename T> struct Rule {
//   virtual RuleResult<T> try_rule(ParseContext &ctx) = 0;
// };