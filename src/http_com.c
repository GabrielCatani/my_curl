#include "my_curl.h"
#include "my_string.h"
#include "http_com.h"

void request(int sockfd, char *http_header) {
  write(sockfd, http_header, my_strlen(http_header));
}

void content_length_format(int sockfd, http_response *http_res) {
  char *line = NULL;
  char *body_lenght = NULL;
  body_lenght = get_header_value(http_res, "Content-Length");
  int length = 0;
  
  if (body_lenght) {
    length = my_atoi(body_lenght);
    free(body_lenght);
  }
  while ((line = my_readline(sockfd))) {
    my_putstr(line, 1);
    length -= my_strlen(line) + 1;
    free(line);
    if (length <= 0) {
      break;
    }
  }
}

void transfer_encoding_format(int sockfd, http_response *http_res) {
  char *line = NULL;
  char *chunk_info = NULL;
  char *tmp = NULL;
  int chunk_len = 0;
  int line_len = 0;
  printf("%s\n", http_res->values[0]);
  tmp = my_readline(sockfd);
  chunk_info = my_strtok(tmp, '\r');
  free(tmp);
  
  if (chunk_info) {
    chunk_len = hex_to_dec(chunk_info);
    free(chunk_info);
  }
  
  while ((line = my_readline(sockfd))) {
    line_len = my_strlen(line);
    my_putstr(line, 1);
    chunk_len -= line_len + 1;
    printf("%d\n", chunk_len);    
    if (line[line_len + 1] == '\r' ||
	!chunk_len) {
      tmp = my_readline(sockfd);
      chunk_info = my_strtok(tmp,'\r');
      free(tmp);
      if (!chunk_info) {
        break;
      }
      else {
       chunk_len = hex_to_dec(chunk_info);
       free(chunk_info);
      }
    }
  }
}


void get_response_and_show(int sockfd, http_response *http_res) {
  char *data_length_control = get_header_value(http_res, "Transfer-Encoding");

  if (data_length_control) {
    transfer_encoding_format(sockfd, http_res);
  }
  else {
    content_length_format(sockfd, http_res);
  }
}

char *get_header_value(http_response *http_res, char *header) {
  char *value = NULL;

  for (int i = 0; i <= http_res->len; i++) {
    if (!(my_strcmp(http_res->headers[i], header))) {
      value = my_strdup(http_res->values[i]);
    }
  }

  return value;
} 

http_response *get_http_response(int sockfd) {
  char *line = NULL;
  http_response *http_res = NULL;
  http_buffer *http_buf = NULL;
  

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
  free(line);
  
  http_res = struct_http_response(http_buf, nbr_lines);
  print_http_buffer(http_buf);  
  destroy_http_buffer(&http_buf);
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
      my_putstr(head->value, 1);
      head = head->next;
    }
  }
}

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
  http_res->len = index;
  
  return http_res;
}

void destroy_http_buffer(http_buffer **head) {

  http_buffer *previous = *head;

  while (*head) {
    *head = (*head)->next;
    free(previous->value);
    free(previous);
    previous = (*head);
  }
}

void destroy_http_response(http_response **head) {
  for(int i = 0; i <= (*head)->len; i++) {
    free((*head)->headers[i]);
    free((*head)->values[i]);
  }
  free((*head)->headers);
  free((*head)->values);
  free((*head));
}
