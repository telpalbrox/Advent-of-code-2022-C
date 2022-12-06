#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long get_number_from_line(const char *line) { return strtol(line, NULL, 10); }

int is_new_elf(const char *line) { return strlen(line) == 1; }

void day1(void) {
  FILE *input = fopen("./input1.txt", "r");
  char buffer[100];
  char *line;
  long elf_index = 0;
  long max_calories = 0;
  long elf_with_max_calories = 0;
  long current_calories = 0;
  while ((line = fgets(buffer, sizeof buffer, input))) {
    if (is_new_elf(line)) {
      if (current_calories > max_calories) {
        max_calories = current_calories;
        elf_with_max_calories = elf_index;
      }
      elf_index++;
      current_calories = 0;
      continue;
    }
    long calories = get_number_from_line(line);
    current_calories = current_calories + calories;
  }
  printf("Max calories: %ld\n", max_calories);
  printf("From elf number: %ld\n", elf_with_max_calories);
}
