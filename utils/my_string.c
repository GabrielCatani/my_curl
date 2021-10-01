#include "my_string.h"
#include <stdio.h>

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

char *my_strjoin(char *s1, char *s2) {
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

char *my_strdup(char *str) {
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

char *my_strsub(char *str, int start, int len) {
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

char *my_strchr(char *str, char c) {
    int len = 0;
    char *ptr = str;

    len = my_strlen(str) + 1;
    while(len--)
    {
        if (*ptr == c)
            return ptr;
        ptr++;
    }

    return NULL;
}

void my_strclr(char **str) {
    if (str != NULL && *str != NULL)
    {
        free(*str);
        *str = NULL;
    }
}

int my_strcmp(char *s1, char *s2) {
  while (*s1 && *s2 && *s1 == *s2) {
    s1++;
    s2++;
  }

  return (*s1 - *s2);
}

int my_strncmp(char *s1, char *s2, int len) {

  while (*s1 && *s2 && *s1 == *s2 && --len > 0) {
    s1++;
    s2++;
  }

  return (*s1 - *s2);  
}

char *get_key(char *str, char sep) {
  if (!str) {
    return NULL;
  }

  char *strip = NULL;
  int index = 0;
  while (str[index] != '\0' && str[index] != sep) {
    index++;
  }
  strip = my_strsub(str, 0, index);
  return strip;
}

char *get_value(char *str, char sep) {
  if (!str) {
    return NULL;
  }

  char *strip = NULL;
  int len = my_strlen(str);
  int index = 0;
  while (str[index] != '\0' && str[index] != sep) {
    index++;
  }

  strip = my_strsub(str, index + 2, len);
  return strip;
}
