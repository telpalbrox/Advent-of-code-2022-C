#include "util.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

char *copy_str(char *str) {
  unsigned long str_len = strlen(str);
  char *new_str = (char *)malloc(str_len + 1);
  strncpy(new_str, str, str_len + 1);
  return new_str;
}

long parse_number(char *str) { return strtol(str, NULL, 10); }

List *list_new() {
  List *this = (List *)malloc(sizeof(List));
  this->capacity = 32;
  this->length = 0;
  this->items = calloc(this->capacity, sizeof(void *));
  return this;
}

void list_free(List *this) {
  free(this->items);
  free(this);
}

void list_push(List *this, void *value) { list_put(this, this->length, value); }

void list_put(List *this, size_t index, void *value) {
  if (this->length >= this->capacity) {
    size_t new_capacity = this->capacity * 2;
    this->items = realloc(this->items, sizeof(void *) * new_capacity);
    this->capacity = new_capacity;
  }
  if (index < this->length) {
    memmove(&this->items[index + 1], &this->items[0],
            (this->length - index) * sizeof(this->items[0]));
  }
  this->items[index] = value;
  this->length++;
}

void *list_remove(List *this, size_t index) {
  assert(index < this->length);
  void *item = this->items[index];
  this->length--;
  if (index < this->length) {
    memmove(&this->items[0], &this->items[index + 1],
            (this->length - index) * sizeof(this->items[0]));
  }
  return item;
}

void *list_pop(List *this) { return list_remove(this, this->length - 1); }

void *list_get(List *this, size_t index) { return this->items[index]; }

void list_unshift(List *this, void *value) { list_put(this, 0, value); }

void *list_get_last(List *this) { return list_get(this, this->length - 1); }

void list_print_content_char(List *this) {
  printf("[");
  for (size_t i = 0; i < this->length; i++) {
    if (i != 0) {
      printf(", ");
    }
    void *value = list_get(this, i);
    printf("%c", value);
  }
  puts("]");
}
