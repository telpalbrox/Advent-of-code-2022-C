#include "day5.h"
#include "util.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_COLUMNS 9

static size_t *get_crates_line(const char *line, size_t *line_crates) {
  int column = 0;
  size_t line_len = strlen(line);
  for (size_t i = 0; i < line_len; i++) {
    if (line[i] == '[') {
      line_crates[column] = line[i + 1];
      i += 3;
      column++;
      continue;
    }
    if (line[i] == ' ') {
      i += 3;
      column++;
    }
  }
  return line_crates;
}

static void parse_move(const char *line, int *count, int *from, int *to) {
  sscanf(line, "move %i from %i to %i", count, from, to);
}

static void process_move(List *from, List *to, int count) {
  List *buffer = list_new();
  for (size_t i = 0; i < count; i++) {
    list_push(buffer, list_pop(from));
  }
  for (size_t i = 0; i < buffer->length; i++) {
    list_push(to, list_get(buffer, i));
  }
  list_free(buffer);
}

static void process_move_9001(List *from, List *to, int count) {
  List *buffer = list_new();
  for (size_t i = 0; i < count; i++) {
    list_push(buffer, list_pop(from));
  }
  for (int i = buffer->length - 1; i >= 0; i--) {
    list_push(to, list_get(buffer, i));
  }
  list_free(buffer);
}

void day5(void) {
  List *stacks[NUMBER_COLUMNS];
  for (size_t i = 0; i < NUMBER_COLUMNS; i++) {
    stacks[i] = list_new();
  }
  List *stacks_9001[NUMBER_COLUMNS];
  FILE *input = fopen("./inputs/input5.txt", "r");
  char *line;
  char buffer[100];
  while ((line = fgets(buffer, sizeof buffer, input))) {
    if (line[0] == '[') {
      size_t line_crates[NUMBER_COLUMNS] = {0};
      get_crates_line(line, line_crates);
      for (int i = 0; i < NUMBER_COLUMNS; i++) {
        // printf("line %i: %c\n", i + 1, line_crates[i]);
        if (line_crates[i]) {
          list_unshift(stacks[i], (void *)line_crates[i]);
        }
      }
      continue;
    }
    if (line[0] == ' ') {
      continue;
    }
    if (line[0] == '\n') {
      for (int i = 0; i < NUMBER_COLUMNS; i++) {
        List *stack_9000 = stacks[i];
        stacks_9001[i] = list_new();
        List *stack_9001 = stacks_9001[i];
        for (size_t j = 0; j < stack_9000->length; j++) {
          list_put(stack_9001, j, list_get(stack_9000, j));
        }
      }
      continue;
    }
    if (line[0] == 'm') {
      int count, from, to;
      parse_move(line, &count, &from, &to);
      // process_move(stacks[from - 1], stacks[to - 1], count);
      process_move_9001(stacks_9001[from - 1], stacks_9001[to - 1], count);
      // printf("parsed move: count %i from %i to %i\n", count, from, to);
      continue;
    }
    break;
  }
  char top_crates[NUMBER_COLUMNS + 1] = {0};
  char top_crates_9001[NUMBER_COLUMNS + 1] = {0};
  for (int i = 0; i < NUMBER_COLUMNS; i++) {
    printf("stack 9000 %i: ", i + 1);
    list_print_content_char(stacks[i]);
    top_crates[i] = (size_t)list_get_last(stacks[i]);
    list_free(stacks[i]);
  }
  for (int i = 0; i < NUMBER_COLUMNS; i++) {
    printf("stack 9001 %i: ", i + 1);
    list_print_content_char(stacks_9001[i]);
    top_crates_9001[i] = (size_t)list_get_last(stacks_9001[i]);
    list_free(stacks_9001[i]);
  }
  printf("top crates 9000: %s\n", top_crates);
  printf("top crates 9001: %s\n", top_crates_9001);
  fclose(input);
}
