#include "day6.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

#define SIGNAL_LENGTH 14

void day6(void) {
  FILE *input = fopen("./inputs/input6.txt", "r");
  List *characters = list_new();
  char ch;
  while ((ch = fgetc(input)) != EOF) {
    list_push(characters, ch);
  }
  list_push(characters, NULL);
  char buffer[SIGNAL_LENGTH + 1] = {0};
  int buffer_index = 0;
  int buffer_start = 0;
  int index = 0;
  while (index < list_length(characters)) {
    char ch = list_get(characters, index);
    if (ch == EOF) {
      printf("not found!\n");
      break;
    }
    if (strchr(buffer, ch)) {
      memset(buffer, 0, SIGNAL_LENGTH);
      buffer_index = 0;
      index = buffer_start + 1;
      continue;
    } else {
      buffer[buffer_index] = ch;
      if (buffer_index == 0) {
        buffer_start = index;
      }
      buffer_index++;
      if (buffer_index == SIGNAL_LENGTH) {
        printf("found!\n");
        break;
      }
    }
    index++;
  }
  printf("index: %i, %s\n", index + 1, buffer);
  list_free(characters);
}
