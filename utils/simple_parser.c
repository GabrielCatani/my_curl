#include "simple_parser.h"

void initialize_host_info(struct host_info **h_info) {
  (*h_info) = (struct host_info *)malloc(sizeof(struct host_info));
  if ((*h_info)) {
    (*h_info)->host = NULL;
    (*h_info)->resource = NULL;
    (*h_info)->request = NULL;
  }
}

struct host_info *parse_usr_url(char *usr_input) {
  struct host_info *h_info = NULL;
  initialize_host_info(&h_info);
  
  if (!my_strncmp("http://", usr_input, 7)) {
    usr_input += 7;
  }
  int index = 0;
  while (usr_input[index] != '/' && usr_input[index] != '\0') {
    index++;
  }
  h_info->host = my_strsub(usr_input, 0, index);
  if (is_in_string(h_info->host, '.') == -1) {
    free(h_info->host);
    h_info->host = NULL;
  }
  if (!usr_input[index]) {
   h_info->resource = my_strsub("/", 0, 1);
  }
  else {
    int len = index + 1;
    while (usr_input[len] != '/' && usr_input[len] != '\0') {
      len++;
    }
    h_info->resource = my_strsub(usr_input, index, len);
  }

  h_info->request = form_request(h_info->host, h_info->resource);

  return h_info;
}

char *form_request(char *host, char *resource) {
  char *request = NULL;
  char *tmp = NULL;

  if (!host || ! resource) {
    my_putstr("Invalid URL format", 1);
    return request;
  }
  request = my_strjoin("GET ", resource);
  tmp = request;
  request = my_strjoin(tmp, " HTTP/1.1\r\n");
  free(tmp);
  tmp = request;
  request = my_strjoin(tmp, "Host: ");
  free(tmp);
  tmp = request;
  request = my_strjoin(tmp, host);
  free(tmp);
  tmp = request;
  request = my_strjoin(tmp, "\r\n\r\n");
  free(tmp);
  
  return request;
}

void destroy_host_info(struct host_info **h_info) {
  free((*h_info)->host);
  free((*h_info)->resource);
  free((*h_info)->request);
  free(*h_info);  
}
