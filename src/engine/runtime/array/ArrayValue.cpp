#include "ArrayValue.hpp"
#include <stdexcept>

size_t ArrayValue::size() const { return elements.size(); }

bool ArrayValue::empty() const { return elements.empty(); }

std::shared_ptr<Value> ArrayValue::get(size_t i) const {
  if (i >= elements.size()) throw std::out_of_range("Array index out of range");

  return elements[i];
}

std::shared_ptr<Value> ArrayValue::get_or_null(size_t i) const {
  if (i >= elements.size()) return nullptr;

  return elements[i];
}

void ArrayValue::set(size_t i, std::shared_ptr<Value> v) {
  if (i >= elements.size()) throw std::out_of_range("Array index out of range");

  elements[i] = std::move(v);
}

void ArrayValue::push(std::shared_ptr<Value> v) { elements.push_back(std::move(v)); }

std::shared_ptr<Value> ArrayValue::pop() {
  if (elements.empty()) throw std::runtime_error("Pop from empty array");

  auto v = elements.back();
  elements.pop_back();
  return v;
}

void ArrayValue::clear() { elements.clear(); }

void ArrayValue::insert(size_t i, std::shared_ptr<Value> v) {
  if (i > elements.size()) throw std::out_of_range("Insert index out of range");

  elements.insert(elements.begin() + i, std::move(v));
}

void ArrayValue::remove(size_t i) {
  if (i >= elements.size()) throw std::out_of_range("Remove index out of range");

  elements.erase(elements.begin() + i);
}
