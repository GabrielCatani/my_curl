#ifndef __HTTP_COM_H__
#define __HTTP_COM_H__
typedef struct http_response http_response;
struct http_response {
  int len;
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
void destroy_http_buffer(http_buffer **head);
void destroy_http_response(http_response **head);
void get_response_and_show(int sockfd, http_response *http_res);
char *get_header_value(http_response *http_res, char *header);
void content_length_format(int sockfd, http_response *http_res);
int get_chunk_size(char *line);
int read_and_print_chunk(int sockfd, int chunk_size);
#define BUFFER_SIZE 512
#endif
