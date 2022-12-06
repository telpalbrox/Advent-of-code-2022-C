#include <stdio.h>
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

void day3(void) {
  FILE *input = fopen("./inputs/input3.txt", "r");
  char *line;
  char buffer[100];
  int priority_sum = 0;
  while ((line = fgets(buffer, sizeof buffer, input))) {
    // line = "vJrwpWtwJgWrhcsFMMfFFhFp";
    char c = find_duplicated(line);
    priority_sum = priority_sum + get_priority_for_character(c);
    // printf("duplicated: %c, priority: %d\n", p,
    // get_priority_for_character(p));
  }
  fclose(input);
  printf("priority_sum: %d\n", priority_sum);
}
