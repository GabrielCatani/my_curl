#include "my_curl.h"
#include "my_string.h"
#include "http_com.h"
#include <string.h>

void request(int sockfd, char *http_header) {
  write(sockfd, http_header, my_strlen(http_header));
}

//TODO: Refactor
// Return Http Response header info: standard Status code and Content Lenght.
char **get_response_header(int sockfd) {
  char *line = NULL;
  char **header_info = NULL;

  header_info = (char **)malloc(sizeof(char *) * 3);
  if (!header_info) {
    return NULL;
  }
  
  while ((line = my_readline(sockfd))) {
    // get the line with the HTTP response code
    if (!my_strncmp(line, "HTTP", 4)) {
      header_info[0] = my_strsub(line, 0, my_strlen(line) - 1);
    }
    // get the line with the lenght of the data to be printed
    else if (!my_strncmp(line, "Content-Length:", 15)) {
      header_info[1] = my_strdup(line);
    }
    //Check if the entire Http Header was read
    else if (!my_strcmp(line, "\r")) {
      break;
    }
    free(line);
  }

  free(line);

  return header_info;
}
