#include "ayla_array.h"

#include <cstdint>
#include <stdlib.h>
#include <string.h>

#define AYLA_ARRAY_INITIAL_CAPACITY 4

static bool ayla_array_reserve(AylaArray *array, size_t capacity) {
  if (!array) { return false; }

  if (capacity <= array->capacity) { return true; }

  if (array->element_size != 0 && capacity > SIZE_MAX / array->element_size) { return false; }

  void *data = realloc(array->data, capacity * array->element_size);

  if (!data) { return false; }

  array->data = data;
  array->capacity = capacity;

  return true;
}

AylaArray ayla_array_make(size_t element_size) {
  AylaArray array = {.data = NULL, .size = 0, .capacity = 0, .element_size = element_size};

  return array;
}

AylaArray ayla_array_from(const void *data, size_t size, size_t element_size) {
  AylaArray array = ayla_array_make(element_size);

  if (!data || size == 0) { return array; }

  if (!ayla_array_reserve(&array, size)) { return array; }

  memcpy(array.data, data, size * element_size);

  array.size = size;

  return array;
}

bool ayla_array_push(AylaArray *array, const void *value) {
  if (!array || !value) { return false; }

  if (array->element_size == 0) { return false; }

  if (array->size == array->capacity) {

    size_t new_capacity;

    if (array->capacity == 0) {
      new_capacity = AYLA_ARRAY_INITIAL_CAPACITY;
    } else {

      if (array->capacity > SIZE_MAX / 2) { return false; }

      new_capacity = array->capacity * 2;
    }

    if (!ayla_array_reserve(array, new_capacity)) { return false; }
  }

  memcpy((char *)array->data + array->size * array->element_size,

         value,

         array->element_size);

  array->size++;

  return true;
}

void *ayla_array_get(AylaArray *array, size_t index) {
  if (!array) { return NULL; }

  if (index >= array->size) { return NULL; }

  return (char *)array->data + index * array->element_size;
}

const void *ayla_array_get_const(const AylaArray *array, size_t index) {
  if (!array) { return NULL; }

  if (index >= array->size) { return NULL; }

  return (const char *)array->data + index * array->element_size;
}

bool ayla_array_set(AylaArray *array, size_t index, const void *value) {
  if (!array || !value) { return false; }

  if (index >= array->size) { return false; }

  memcpy((char *)array->data + index * array->element_size,

         value,

         array->element_size);

  return true;
}

bool ayla_array_pop(AylaArray *array) {
  if (!array || array->size == 0) { return false; }

  array->size--;

  return true;
}

void ayla_array_clear(AylaArray *array) {
  if (!array) { return; }

  array->size = 0;
}

void ayla_array_free(AylaArray *array) {
  if (!array) { return; }

  free(array->data);

  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
  array->element_size = 0;
}