#ifndef __MY_STRING_H__
#define __MY_STRING_H__
#include <stdlib.h>
#include <unistd.h>
int is_in_string(char *str, char c);
void my_memset(char *dst, char value, int len);
void my_putstr(char *str, int new_line);
int my_strlen(char *str);
char *my_strjoin(char *s1, char *s2);
char *my_strdup(char *str);
char *my_strsub(char *str, int start, int len);
char *my_strchr(char *str, char c);
void my_strclr(char **str);
//my_readline functions
void read_and_save(int fd, char **line);
char *output_line(char **line, int len);
int line_len(char **line);
char *my_readline(int fd);
int my_strcmp(char *s1, char *s2);
int my_strncmp(char *s1, char *s2, int len);
char *get_key(char *str, char sep);
char *get_value(char *str, char sep);
int my_isalpha(int c);
int my_atoi(char *str);
int my_tolower(int c);
char *my_strncpy(char *dst, char *src, int n);
char *my_strtok(char *str, char delim);
int hex_letter_value(char hex_digit);
int hex_to_dec(char *chunk_info);
int power_of(int base, int power);
int ascii_to_nbr(char c);
#endif
