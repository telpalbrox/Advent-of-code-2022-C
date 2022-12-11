#include <stdlib.h>
#include <string.h>

char *copy_str(char *str) {
  unsigned long str_len = strlen(str);
  char *new_str = (char *)malloc(str_len + 1);
  strncpy(new_str, str, str_len + 1);
  return new_str;
}

long parse_number(char *str) { return strtol(str, NULL, 10); }
