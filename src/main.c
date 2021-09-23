#include "my_curl.h"

int main(void) {

  //Test open_connection
  struct sockaddr_in *socket_info = NULL;
  char **header_info = NULL;
  int sockfd = 0;
  char *http_header = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
  socket_info = set_socket(get_host_info("www.example.com"));

  sockfd = open_connection(socket_info);
  if (sockfd > 2) {
    request(sockfd, http_header);
    header_info =  get_response_header(sockfd);
    printf("HTTP Response: %s.  %s\n", header_info[0], header_info[1]);
    free(header_info[0]);
    free(header_info[1]);
    free(header_info);
  }
  close_connection(socket_info, sockfd);

  sockfd = 0;
  socket_info = set_socket(get_host_info("not_valid_URL"));

  sockfd = open_connection(socket_info);

  close_connection(socket_info, sockfd);  

  return 0;
}
