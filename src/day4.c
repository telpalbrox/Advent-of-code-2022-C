#include "day4.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Range {
  int start;
  int end;
} Range;

static short range_fully_contains(Range *range1, Range *range2) {
  if (range1->start <= range2->start && range1->end >= range2->end) {
    return 1;
  }
  return 0;
}

static short range_fully_contains_each_other(Range *range1, Range *range2) {
  if (range_fully_contains(range1, range2) ||
      range_fully_contains(range2, range1)) {
    return 1;
  }
  return 0;
}

static short range_overlaps(Range *range1, Range *range2) {
  if ((range1->end >= range2->start && range1->end <= range2->end) ||
      (range1->start <= range2->end && range1->start >= range2->start)) {
    return 1;
  }
  return 0;
}

static short range_overlaps_each_other(Range *range1, Range *range2) {
  if (range_fully_contains_each_other(range1, range2)) {
    return 1;
  }
  if (range_overlaps(range1, range2)) {
    return 1;
  }
  return 0;
}

#define reset_range_buffer()                                                   \
  (buffer_index = 0, memset(&range_buffer, 0, sizeof range_buffer))

void day4(void) {
  char buffer[100];
  char *line;
  FILE *input = fopen("./inputs/input4.txt", "r");
  int fully_contained_ranges = 0;
  int overlapped_ranges = 0;
  while ((line = fgets(buffer, sizeof buffer, input))) {
    int buffer_index = 0;
    char range_buffer[RANGE_BUFFER_SIZE] = {0};
    int range_start = 0;
    int range_end = 0;
    Range first_range;
    Range second_range;
    for (char *c = line; *c != 0; c++) {
      if (isdigit(*c)) {
        range_buffer[buffer_index] = *c;
        buffer_index++;
        continue;
      } else if (*c == '-') {
        range_start = (int)parse_number(range_buffer);
        reset_range_buffer();
        continue;
      } else if (*c == ',') {
        range_end = (int)parse_number(range_buffer);
        reset_range_buffer();
        first_range.start = range_start;
        first_range.end = range_end;
        continue;
      } else if (*c == '\n') {
        range_end = (int)parse_number(range_buffer);
        reset_range_buffer();
        second_range.start = range_start;
        second_range.end = range_end;
        // printf("Parsed range(%d,%d) and range(%d,%d)", first_range.start,
        //        first_range.end, second_range.start, second_range.end);
        if (range_fully_contains_each_other(&first_range, &second_range)) {
          fully_contained_ranges++;
          // printf(" they contain eachother");
        }
        if (range_overlaps_each_other(&first_range, &second_range)) {
          overlapped_ranges++;
          // printf(" they overlap eachother");
        }
        // printf("\n");
        break;
      }
      fprintf(stderr, "Unexpected character %c (%d)\n", *c, *c);
      abort();
    }
    // printf("line: %s\n", line);
  }
  printf("fully_contained_ranges: %d\n", fully_contained_ranges);
  printf("overlapped_ranges: %d\n", overlapped_ranges);
}
