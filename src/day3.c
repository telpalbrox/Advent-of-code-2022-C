#include "day3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_priority_for_character(char c) {
  if (c >= 97) {
    return c - 96;
  }
  return c - 38;
}

char find_duplicated(char *rucksack) {
  unsigned long len = strlen(rucksack);
  unsigned long half_len = len / 2;
  // printf("first half: %.*s\n", (int)half_len, rucksack);
  // printf("second half: %.*s\n", (int)half_len, rucksack + half_len);
  for (size_t i = 0; i < half_len; i++) {
    char to_find = rucksack[i];
    for (size_t j = half_len; j < len; j++) {
      char character = rucksack[j];
      if (to_find == character) {
        return character;
      }
    }
  }
  return '\0';
}

char find_common_item(char **rucksack_group) {
  char *first_rucksack = rucksack_group[0];
  char found = 0;
  for (char *item = &first_rucksack[0]; *item && *item != '\n'; item++) {
    int not_found_item = 0;
    while (!found && !not_found_item) {
      for (size_t rucksack_index = 1; rucksack_index < RUCKSACK_GROUP_SIZE;
           rucksack_index++) {
        char *rucksack = rucksack_group[rucksack_index];
        if (strchr(rucksack, *item)) {
          found = *item;
        } else {
          not_found_item = 1;
          found = 0;
          break;
        }
      }
    }
  }
  if (found == 0) {
    fprintf(stderr, "Common badge not found!\n");
    abort();
  }
  return found;
}

char *copy_str(char *str) {
  unsigned long str_len = strlen(str);
  char *new_str = (char *)malloc(str_len + 1);
  strncpy(new_str, str, str_len + 1);
  return new_str;
}

void day3(void) {
  FILE *input = fopen("./inputs/input3.txt", "r");
  char *line;
  char buffer[100];
  char *rucksack_group[RUCKSACK_GROUP_SIZE];
  int index = 0;
  int priority_sum = 0;
  int common_badges_sum = 0;
  while ((line = fgets(buffer, sizeof buffer, input))) {
    char c = find_duplicated(line);
    priority_sum = priority_sum + get_priority_for_character(c);
    size_t group_index = index % RUCKSACK_GROUP_SIZE;
    rucksack_group[group_index] = copy_str(line);
    if (group_index == RUCKSACK_GROUP_SIZE - 1) {
      char item = find_common_item(rucksack_group);
      for (size_t i = 0; i < RUCKSACK_GROUP_SIZE; i++) {
      }
      common_badges_sum = common_badges_sum + get_priority_for_character(item);
    }
    index++;
  }
  fclose(input);
  printf("priority_sum: %d\n", priority_sum);
  printf("common_badges_sum: %d\n", common_badges_sum);
}
