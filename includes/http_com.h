#ifndef __HTTP_COM_H__
#define __HTTP_COM_H__
typedef struct http_response http_response;
struct http_response {
  char **headers;
  char **values;  
};
typedef struct http_buffer http_buffer;
struct http_buffer {
  char *value;
  struct http_buffer *next;
};
http_buffer *new_line(char *value);
void add_line(http_buffer **head, char *value);
void print_http_buffer(http_buffer *head);
http_response *get_http_response(int sockfd);
http_response *struct_http_response(http_buffer *http_buf, int nbr_lines);
void request(int sockfd, char *http_header);
#define BUFFER_SIZE 512
#endif
