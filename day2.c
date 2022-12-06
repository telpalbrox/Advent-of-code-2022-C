#include "day2.h"
#include <stdio.h>
#include <stdlib.h>

char get_shape_for_outcome(char oponent_shape, char outcome) {
  switch (outcome) {
  case 'X': // lose
    switch (oponent_shape) {
    case 'A':     // rock
      return 'Z'; // scissors
    case 'B':     // paper
      return 'X'; // rock
    case 'C':     // scissors
      return 'Y'; // paper
    }
    break;
  case 'Y': // draw
    switch (oponent_shape) {
    case 'A':     // rock
      return 'X'; // rock
    case 'B':     // paper
      return 'Y'; // paper
    case 'C':     // scissors
      return 'Z'; // scissors
    }
    break;
  case 'Z': // win
    switch (oponent_shape) {
    case 'A':     // rock
      return 'Y'; // paper
    case 'B':     // paper
      return 'Z'; // scissors
    case 'C':     // scissors
      return 'X'; // rock
    }
    break;
  }
  fprintf(stderr, "Wrong shape %c or outcome %c", oponent_shape, outcome);
  abort();
}

int calculate_round_outcome(char oponent_shape, char my_shape) {
  int score = 0;
  switch (my_shape) {
  case 'Y': // paper
    score = 2;
    switch (oponent_shape) {
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
    switch (oponent_shape) {
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
    switch (oponent_shape) {
    case 'A': // rock
      return score + 0;
    case 'B': // paper
      return score + 6;
    case 'C': // scissors
      return score + 3;
    }
    break;
  }
  fprintf(stderr, "Wrong shape: %c or %c", my_shape, oponent_shape);
  abort();
}

void day2(void) {
  FILE *input = fopen("./input2.txt", "r");
  char *line;
  char buffer[100];
  int score_part_one = 0;
  int score_part_two = 0;
  while ((line = fgets(buffer, sizeof buffer, input))) {
    char oponent_shape = line[0];
    char my_shape = line[2];
    score_part_one =
        score_part_one + calculate_round_outcome(oponent_shape, my_shape);
    score_part_two =
        score_part_two +
        calculate_round_outcome(oponent_shape,
                                get_shape_for_outcome(oponent_shape, my_shape));
    // printf("oponent_shape %c, my_shape %c\n", oponent_shape, my_shape);
    // printf("get_shape_for_outcome(%c, %c) -> %c\n", oponent_shape, my_shape,
    //       get_shape_for_outcome(oponent_shape, my_shape));
  }
  fclose(input);
  printf("score_part_one: %d\n", score_part_one);
  printf("score_part_two: %d\n", score_part_two);
}
