#pragma once
#include <stdio.h>

char *copy_str(char *str);
long parse_number(char *str);

typedef struct List {
  size_t capacity;
  size_t length;
  void **items;
} List;

List *list_new();
void list_push(List *list, void *value);
void list_put(List *list, size_t index, void *value);
void *list_remove(List *list, size_t index);
void *list_pop(List *list);
void *list_get(List *list, size_t index);
void list_unshift(List *list, void *value);
void list_print_content_char(List *list);
void list_free(List *list);
void *list_get_last(List *list);
