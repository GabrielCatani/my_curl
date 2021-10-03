#include "my_string.h"
#include <stdio.h>

void my_memset(char *dst, char value, int len)
{
  for (int i = 0; i < len; i++)
  {
    dst[i] = value;
  }
}

int my_strlen(char *str)
{

  int len = 0;
  if (str)
  {
    while (str[len] != '\0')
    {
      len++;
    }
  }

  return len;
}

void my_putstr(char *str, int new_line)
{

  int len = my_strlen(str);
  if (str)
  {
    write(1, str, len);
  }
  if (new_line)
  {
    write(1, "\n", 1);
  }
}

char *my_strjoin(char *s1, char *s2)
{
  int i = 0;
  char *result;

  result = (char *)malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2)) + 1);
  if (!result || !s1 || !s2)
    return NULL;

  while (*s1)
    result[i++] = *s1++;

  while (*s2)
    result[i++] = *s2++;

  result[i] = '\0';

  return result;
}

char *my_strdup(char *str)
{
  char *cpy_str = NULL;
  int index = 0;

  cpy_str = (char *)malloc((my_strlen(str) + 1) * sizeof(char));
  if (!cpy_str || !str)
    return NULL;

  while (str[index] != '\0')
  {
    cpy_str[index] = str[index];
    index++;
  }

  cpy_str[index] = '\0';

  return cpy_str;
}

char *my_strsub(char *str, int start, int len)
{
  char *ptr;
  int i;

  ptr = (char *)malloc(sizeof(char) * (len + 1));
  if (!ptr || !str)
    return NULL;

  str = str + start;
  i = 0;
  while (i < (len - start))
  {
    ptr[i] = str[i];
    i++;
  }

  ptr[i] = '\0';
  return ptr;
}

char *my_strchr(char *str, char c)
{
  int len = 0;
  char *ptr = str;

  len = my_strlen(str) + 1;
  while (len--)
  {
    if (*ptr == c)
      return ptr;
    ptr++;
  }

  return NULL;
}

void my_strclr(char **str)
{
  if (str != NULL && *str != NULL)
  {
    free(*str);
    *str = NULL;
  }
}

int my_strcmp(char *s1, char *s2)
{
  while (*s1 && *s2 && *s1 == *s2)
  {
    s1++;
    s2++;
  }

  return (*s1 - *s2);
}

int my_strncmp(char *s1, char *s2, int len)
{

  while (*s1 && *s2 && *s1 == *s2 && --len > 0)
  {
    s1++;
    s2++;
  }

  return (*s1 - *s2);
}

char *get_key(char *str, char sep)
{
  if (!str)
  {
    return NULL;
  }

  char *strip = NULL;
  int index = 0;
  while (str[index] != '\0' && str[index] != sep)
  {
    index++;
  }
  strip = my_strsub(str, 0, index);
  return strip;
}

char *get_value(char *str, char sep)
{
  if (!str)
  {
    return NULL;
  }

  char *strip = NULL;
  int len = my_strlen(str);
  int index = 0;
  while (str[index] != '\0' && str[index] != sep)
  {
    index++;
  }

  strip = my_strsub(str, index + 2, len);
  return strip;
}

int my_isalpha(int c)
{
  if ((c >= 'A' && 'Z' >= c) || (c >= 'a' && 'z' >= c))
    return (1);
  return (0);
}

int my_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    int index = 0;

    while ((*str >= 9 && *str <= 13) || *str == ' ')
        ++str;

    if (str[index] == '-')
        sign = -1;

    while (str[index])
    {
        if (str[index] >= '0' && str[index] <= '9')
        {
            while (str[index] >= '0' && str[index] <= '9')
            {
                result = (10 * result) + str[index] - 48;
                index++;
            }
            break;
        }
        index++;
    }

    return result * sign;
}

int my_tolower(int c)
{
  return ((c >= 'A' && c <= 'Z') ? c + 32 : c);
}

char *my_strncpy(char *dst, char *src, int n)
{
  int i;

  i = 0;
  while (i < n && src[i])
  {
    dst[i] = src[i];
    i += 1;
  }
  while (i < n)
  {
    dst[i] = '\0';
    i += 1;
  }
  return (dst);
}

char *my_strtok(char *str, char delim)
{
  char *stock = NULL;
  char *ptr;
  int flg;

  flg = 0;
  ptr = NULL;
  if (str != NULL)
    stock = my_strdup(str);
  while (*stock != '\0')
  {
    if (flg == 0 && *stock != delim)
    {
      flg = 1;
      ptr = stock;
    }
    else if (flg == 1 && *stock == delim)
    {
      *stock = '\0';
      stock += 1;
      break;
    }
    stock += 1;
  }
  return (ptr);
}

int power_of(int base, int power) {
  if (power == 0) {
    return 1;
  }
  else if (power == 1) {
    return base;
  }

  int result = base;
  while (power-- > 1) {
    result *= base;
  }

  return result;
}

int ascii_to_nbr(char c) {
  if (c >= '0' && c <= '9') {
    return c - 48; 
  }
  return -1;
}

int hex_letter_value(char hex_digit) {
  char hex_table[] = {'a', 'b', 'c','d','e','f'};
  int index = 0;
  
  while (index++ < 6) {
    if (hex_table[index] == hex_digit) {
      return (10 + index);
    }
  }
  return -1;
}

int hex_to_dec(char *chunk_info) {
  int dec = 0;
  int digits = my_strlen(chunk_info) - 1;
  int power = digits;
  int index = 0;
  while (index <= digits) {
    if (chunk_info[index] > '9') {
      dec += (hex_letter_value(chunk_info[index]) * power_of(16, power));
    }
    else {
      dec += (ascii_to_nbr(chunk_info[index]) * power_of(16, power));
    }
    index++;
    power--;
  }
  return dec;
}
