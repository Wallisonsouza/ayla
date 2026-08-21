#ifndef AYLA_ARRAY_H
#define AYLA_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct AylaArray {
  void *data;

  size_t size;
  size_t capacity;
  size_t element_size;
} AylaArray;

/*
 * Cria um array vazio.
 *
 * element_size:
 * tamanho, em bytes, de cada elemento.
 */
AylaArray ayla_array_make(size_t element_size);

/*
 * Cria um array copiando os elementos de um buffer.
 */
AylaArray ayla_array_from(const void *data, size_t size, size_t element_size);

/*
 * Adiciona um elemento ao final do array.
 */
bool ayla_array_push(AylaArray *array, const void *value);

/*
 * Retorna um ponteiro para o elemento.
 *
 * Retorna NULL se o índice for inválido.
 */
void *ayla_array_get(AylaArray *array, size_t index);

/*
 * Versão somente leitura de get.
 */
const void *ayla_array_get_const(const AylaArray *array, size_t index);

/*
 * Substitui um elemento existente.
 */
bool ayla_array_set(AylaArray *array, size_t index, const void *value);

/*
 * Remove o último elemento.
 */
bool ayla_array_pop(AylaArray *array);

/*
 * Remove todos os elementos, mas mantém a capacidade.
 */
void ayla_array_clear(AylaArray *array);

/*
 * Libera a memória do array.
 */
void ayla_array_free(AylaArray *array);

#endif