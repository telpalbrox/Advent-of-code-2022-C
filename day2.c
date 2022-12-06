#include "day2.h"
#include <stdio.h>
#include <stdlib.h>

int calculate_round_outcome(char oponent_shape, char my_shape) {
  int score = 0;
  switch(my_shape) {
    case 'Y': // paper
      score = 2;
      switch(oponent_shape) {
        case 'A': // rock
          return score + 6;
        case 'B': // paper
          return score + 3;
        case 'C': // scissors
          return score + 0;
      }
      break;
    case 'X': // rock
      score = 1;
      switch(oponent_shape) {
        case 'A': // rock
          return score + 3;
        case 'B': // paper
          return score + 0;
        case 'C': // scissors
          return score + 6;
      }
      break;
    case 'Z': // scissors
      score = 3;
      switch(oponent_shape) {
        case 'A': // rock
          return score + 0;
        case 'B': // paper
          return score + 6;
        case 'C': // scissors
          return score + 3;
      }
      break;
  }
  fprintf("Wrong shape: %c or %c", my_shape, oponent_shape);
  abort();
}

void day2(void) {
  FILE *input = fopen("./input2.txt", "r");
  char *line;
  char buffer[100];
  int score = 0;
  while ((line = fgets(buffer, sizeof buffer, input))) {
    char oponent_shape = line[0];
    char my_shape = line[2];
    score = score + calculate_round_outcome(oponent_shape, my_shape);
    // printf("oponent_shape %c, my_shape %c\n", oponent_shape, my_shape);
  }
  fclose(input);
  printf("score: %d\n", score);
}
