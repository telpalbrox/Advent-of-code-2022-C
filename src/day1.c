#include "day1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long get_number_from_line(const char *line) { return strtol(line, NULL, 10); }

int is_new_elf(const char *line) { return strlen(line) == 1; }

void update_top_elfs_calories(long *top_elfs_calories, long new_calories) {
  for (size_t index = 0; index < TOP_SIZE; index++) {
    long calories = top_elfs_calories[index];
    // printf("iterating over top_elfs_calories, %d, %ld, %ld\n", index,
    // calories, new_calories);
    if (new_calories > calories) {
      top_elfs_calories[index] = new_calories;
      // We need to recalculate just in case the previous calories are stil
      // insde the top.
      update_top_elfs_calories(top_elfs_calories, calories);
      break;
    }
  }
}

void day1(void) {
  FILE *input = fopen("./inputs/input1.txt", "r");
  long top_elfs_calories[TOP_SIZE] = {0};
  char buffer[100];
  char *line;
  long elf_index = 0;
  long max_calories = 0;
  long elf_with_max_calories = 0;
  long current_calories = 0;
  while ((line = fgets(buffer, sizeof buffer, input))) {
    if (is_new_elf(line)) {
      update_top_elfs_calories(top_elfs_calories, current_calories);
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
  fclose(input);
  printf("Max calories: %ld\n", max_calories);
  printf("From elf number: %ld\n", elf_with_max_calories);
  printf("Top:\n");
  long total_top_calories = 0;
  for (size_t index = 0; index < TOP_SIZE; index++) {
    long calories = top_elfs_calories[index];
    printf("Position %ld: %ld\n", index, calories);
    total_top_calories = total_top_calories + calories;
  }
  printf("Top calories sum: %ld\n", total_top_calories);
}
