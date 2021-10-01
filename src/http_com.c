#include "my_curl.h"
#include "my_string.h"
#include "http_com.h"
#include <string.h>

void request(int sockfd, char *http_header) {
  write(sockfd, http_header, my_strlen(http_header));
}

//TODO: Refactor
http_response *get_http_response(int sockfd) {
  char *line = NULL;
  http_response *http_res;
  http_buffer *http_buf = NULL;
  
  http_res = (http_response *)malloc(sizeof(http_response));
  if (!http_res) {
    return NULL;
  }

  int nbr_lines = 0;
  while ((line = my_readline(sockfd))) {
    //Check if the entire Http Header was read
    if (!my_strcmp(line, "\r")) {
      break;
    }
    add_line(&http_buf, line);
    free(line);
    nbr_lines++;
  }

  struct_http_response(http_buf, nbr_lines);
  return http_res;
}

http_buffer *new_line(char *value) {
  http_buffer *line = NULL;

  line = (http_buffer *)malloc(sizeof(http_buffer));
  if (line) {
    line->value = my_strdup(value);
    line->next = NULL;
  }
  return line;
}

void add_line(http_buffer **head, char *value) {
  http_buffer *ptr = (*head);

  if (!(*head)) {
    (*head) = new_line(value);
  }
  else {
    while (ptr->next) {
      ptr = ptr->next;
    }
    ptr->next = new_line(value);
  }
}

void print_http_buffer(http_buffer *head) {

  if (head) {
    while (head) {
      printf("%s\n", head->value);
      head = head->next;
    }
  }
}

//TODO: return, in main, crashing when accessing http_res elements
http_response *struct_http_response(http_buffer *http_buf, int nbr_lines) {
  http_response *http_res = NULL;

  http_res = (http_response *)malloc(sizeof(http_response));
  if (!http_buf || !http_res) {
    return NULL;
  }
  
  http_res->headers = (char **)malloc(sizeof(char *) * nbr_lines);
  http_res->values = (char **)malloc(sizeof(char *) * nbr_lines);
 
  if (!http_res->headers || !http_res->values) {
    return NULL;
  }

  int index = 0;
  http_res->headers[index] = my_strdup("Status Code");
  http_res->values[index] = get_key(http_buf->value, ':');
  http_buf = http_buf->next;
  while (http_buf) {
    index++;
    http_res->headers[index] = get_key(http_buf->value, ':');
    http_res->values[index] = get_value(http_buf->value, ':');
    http_buf = http_buf->next;
  }
  
  return http_res;
}
