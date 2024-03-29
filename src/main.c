#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"
#include <stdio.h>

int main(int argc, char **args) {
  if (argc != 2) {
    fprintf(stderr, "You need to pass the day numner as argument!\n");
    return 1;
  }

  switch (args[1][0]) {
  case '1':
    day1();
    break;
  case '2':
    day2();
    break;
  case '3':
    day3();
    break;
  case '4':
    day4();
    break;
  case '5':
    day5();
    break;
  case '6':
    day6();
    break;
  case '7':
    day7();
    break;
  default:
    fprintf(stderr, "Unknown day %s\n", args[1]);
  }
  return 0;
}
