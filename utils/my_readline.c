#include <unistd.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <fcntl.h>
#define READLINE_READ_SIZE 1
#include "my_string.h"

#include <stdio.h>

typedef struct circularIndexes circularIndexes;
struct circularIndexes {
  int readIndex;
  int writeIndex;
  int used;
  int size;
};

char *my_strndup(char *str, int len)
{
  char *cpy_str = NULL;
  int index = 0;

  cpy_str = (char *)malloc((my_strlen(str) + 1) * sizeof(char));
  if (!cpy_str || !str)
    return NULL;

  while (str[index] != '\0' && index < len)
  {
    cpy_str[index] = str[index];
    index++;
  }

  cpy_str[index] = '\0';

  return cpy_str;
}

void writeValue(char *circularBuffer, char *line_chunk, struct circularIndexes *c_indexes) {
  int index = 0;
  while(line_chunk[index] != '\0' && index < c_indexes->size) {
    circularBuffer[c_indexes->writeIndex] = line_chunk[index];
    c_indexes->writeIndex++;
    c_indexes->used++;
    index++;
    if (c_indexes->writeIndex == c_indexes->size) {
      c_indexes->writeIndex = 0;
    }
  }
}

char *readValue(char *circularBuffer, struct circularIndexes *c_indexes) {
  char *str = NULL;
  int index = 0;

  str = (char *)malloc(sizeof(char) * (c_indexes->used + 1));
  if (!str) {
    return NULL;
  }
  while(c_indexes->used > 0) {
    str[index] = circularBuffer[c_indexes->readIndex];
    c_indexes->readIndex++;
    c_indexes->used--;
    index++;
    if (c_indexes->readIndex == c_indexes->size) {
      c_indexes->readIndex = 0;
    }
  }
  str[index] = '\0';
  
  return str;
}

void   circular_controls_init(char *buffer, struct circularIndexes *c_indexes) {

  if (!buffer) {
    c_indexes->readIndex = 0;
    c_indexes->writeIndex = 0;
    c_indexes->used = 0;
    c_indexes->size = READLINE_READ_SIZE;
  }
}

//TODO
void append_to_line(char **line, char *str, int len) {
  char *tmp = NULL;
  char *str_chunk = my_strndup(str, len);
  
  if (*line) {
    tmp = (*line);
    (*line) = my_strjoin(tmp, str_chunk);
    free(tmp);
  }
  else {
    (*line) = my_strdup(str_chunk);
  }
  free(str_chunk);
}

void prepend_to_line(char **line, char *str, int len) {
  char *tmp = NULL;
  char *str_chunk = my_strndup(str, len);
  
  if (*line) {
    tmp = (*line);
    (*line) = my_strjoin(str_chunk, tmp);
    free(tmp);
  }
  else {
    (*line) = my_strdup(str_chunk);
  }
  free(str_chunk);
}

char *my_readline(int fd) {
  char *line = NULL;
  static char circularBuffer[READLINE_READ_SIZE];
  char read_buffer[READLINE_READ_SIZE + 1];
  int line_len = 0;
  static circularIndexes c_indexes;
  char *new_line_pos = NULL;
  char *read_circ = NULL;

  if (fd == -1) {
    return line;
  }  
  circular_controls_init(circularBuffer, &c_indexes);

  //handle rest
  if (c_indexes.used > 0) {
    read_circ = readValue(circularBuffer, &c_indexes);
    if ((new_line_pos = my_strchr(read_circ, '\n'))) {
      line = my_strndup(read_circ, (new_line_pos - read_circ));
      writeValue(circularBuffer, new_line_pos + 1, &c_indexes);
      free(read_circ);
      return line; 
    }
    line = my_strdup(read_circ);
    free(read_circ);
  }

  while ((line_len = read(fd, read_buffer, READLINE_READ_SIZE))) {
    if (line_len == -1) {
      return NULL;
    }
    read_buffer[line_len] = '\0';

    if ((new_line_pos = my_strchr(read_buffer, '\n'))) {
      append_to_line(&line, read_buffer, (new_line_pos - read_buffer));
      writeValue(circularBuffer, new_line_pos + 1, &c_indexes);
      break;
    }
    else {
      append_to_line(&line, read_buffer, my_strlen(read_buffer));
    }
  }

  return line;
}
