#include "my_curl.h"

//$> my_curl "www.whatever.com"
int main(int argc, char *argv[])
{

    //Test open_connection
  struct sockaddr_in *socket_info = NULL;
  http_response *http_res = NULL;
  int sockfd = 0;
  char *http_header = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
  socket_info = set_socket(get_host_info("www.example.com"));

  sockfd = open_connection(socket_info);
  if (sockfd > 2)
  {
    request(sockfd, http_header);
    http_res = get_http_response(sockfd);
    printf("%s\n", http_res->headers[1]);
  }
  close_connection(socket_info, sockfd);

  sockfd = 0;
  socket_info = set_socket(get_host_info("not_valid_URL"));

  sockfd = open_connection(socket_info);

  close_connection(socket_info, sockfd);

  return 0;
}
