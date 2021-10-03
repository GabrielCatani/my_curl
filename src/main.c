#include "my_curl.h"

//$> my_curl "www.whatever.com"
int main(int argc, char **argv)
{
  parsed_url *purl = purl_initializer();
  if (argc != 2) {
    my_putstr(argv[0], 0);
    my_putstr(" :usage [url]", 1);
    return 1;
  }
  //TODO: replace stirng literal with argv[1]
  purl = parse_url("http:www.google.com");
  
  struct sockaddr_in *socket_info = NULL;
  http_response *http_res = NULL;
  int sockfd = 0;

  //TODO: Form Http request header based on parsed user input
  //TODO: free Parser struct, and http_header, after use
  char *http_header = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
  socket_info = set_socket(get_host_info("www.google.com"));
  sockfd = open_connection(socket_info);
  if (sockfd > 2)
  {
    request(sockfd, http_header);
    http_res = get_http_response(sockfd);
    get_response_and_show(sockfd, http_res);
    destroy_http_response(&http_res);
  }
  close_connection(socket_info, sockfd);

  return 0;
}
