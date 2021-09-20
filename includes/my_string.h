#ifndef __MY_STRING_H__
#define __MY_STRING_H__
#include <stdlib.h>
#include <unistd.h>
void my_memset(char *dst, char value, int len);
void my_putstr(char *str, int new_line);
int my_strlen(char *str);
#endif
