#include "my_string.h"

void my_memset(char *dst, char value, int len) {
  for (int i = 0; i < len; i++) {
    dst[i] = value;
  }
}

int my_strlen(char *str) {

  int len = 0;
  if (str) {
    while (str[len] != '\0') {
      len++;
    }
  }

  return len;
}

void my_putstr(char *str, int new_line) {

  int len = my_strlen(str);
  if (str) {
    write(1, str, len);
  }
  if (new_line) {
    write(1, "\n", 1);
  }
}
