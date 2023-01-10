#include "day6.h"
#include <stdio.h>
#include <string.h>

#define SIGNAL_LENGTH 4

void day6(void) {
  FILE *input = fopen("./inputs/input6.txt", "r");
  char buffer[SIGNAL_LENGTH + 1] = {0};
  int buffer_index = 0;
  int index = 0;
  char ch;
  while ((ch = fgetc(input))) {
    if (buffer_index != 4 && strchr(buffer, ch)) {
      memset(buffer, 0, SIGNAL_LENGTH);
      buffer_index = 0;
    } else {
      buffer[buffer_index] = ch;
      buffer_index++;
      if (buffer_index == 4) {
        printf("found!\n");
        break;
      }
    }
    index++;
  }
  printf("index: %i, %s\n", index - 1, buffer);
}
