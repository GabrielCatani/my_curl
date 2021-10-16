#include "simple_parser.h"

char *parse_usr_url(char *usr_input) {
  char *host = NULL;
  char *resource = NULL;
  char *request = NULL;
  
  if (!my_strncmp("http://", usr_input, 7)) {
    usr_input += 7;
  }
  int index = 0;
  while (usr_input[index] != '/' && usr_input[index] != '\0') {
    index++;
  }
  host = my_strsub(usr_input, 0, index);
  if (!usr_input[index]) {
    resource = my_strsub("/", 0, 1);
  }
  else {
    int len = index + 1;
    while (usr_input[len] != '/' && usr_input[len] != '\0') {
      len++;
    }
    resource = my_strsub(usr_input, index, len);
  }

  request = form_request(host, resource);
  free(host);
  free(resource);
  return request;
}

char *form_request(char *host, char *resource) {
  char *request = NULL;
  char *tmp = NULL;

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
