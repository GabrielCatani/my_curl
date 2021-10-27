#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include "my_string.h"
#define READLINE_READ_SIZE 7

void read_and_save(int fd, char **line) {
    int rd = 0;
    char buf[READLINE_READ_SIZE + 1];
    char *tmp = NULL;

    while ((rd = read(fd, buf, READLINE_READ_SIZE)))
    {
        if (rd == -1)
            break;
        buf[rd] = '\0';
        if (*line)
        {
            tmp = my_strjoin(*line, buf);
            free(*line);
            *line = tmp;
        }
        else
            *line = my_strdup(buf);

        if (my_strchr(*line, '\n'))
            break;
    }
}

char *output_line(char **line, int len) {
    char *result = NULL;
    char *tmp = NULL;

    if ((*line)[len] == '\n')
    {
        result = my_strsub((*line), 0, len);
        tmp = my_strdup(&(*line)[len + 1]);
        free(*line);
        *line = tmp;
        if ((*(*line)) == '\0')
          my_strclr(line);
    }
    else
    {
        result = my_strdup(*line);
        my_strclr(line);
    }

    return result;
}

int line_len(char **line) {
    int len = 0;

    if (*line)
    {
      while ((*line)[len] != '\n' && (*line)[len] != '\0')
        len++;
    }
    else
      return -1;

    return len;
}

char *my_readline(int fd) {
    static char *line[4096];
    int len = 0;
    char *result = NULL; 

	if (fd < 0)
	 return NULL;
    
    read_and_save(fd, line);

    if ((len = line_len(line)) < 0)
     return NULL;

    result = output_line(line, len);

    return result;
}
