#include "my_curl.h"

//$> my_curl "www.whatever.com"
int main(void)
{
  parsed_url *purl = purl_initializer();
  purl = parse_url("http:www.google.com");
  //Test open_connection
  // struct sockaddr_in *socket_info = NULL;
  // http_response *http_res = NULL;
  // int sockfd = 0;
  // char *http_header = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
  // socket_info = set_socket(get_host_info("www.example.com"));

  // sockfd = open_connection(socket_info);
  // if (sockfd > 2)
  // {
  //   request(sockfd, http_header);
  //   http_res = get_http_response(sockfd);
  //   get_response_and_show(sockfd, http_res);
  //   destroy_http_response(&http_res);
  // }
  // close_connection(socket_info, sockfd);

  // sockfd = 0;
  // socket_info = set_socket(get_host_info("not_valid_URL"));

  // sockfd = open_connection(socket_info);

  // close_connection(socket_info, sockfd);

  return 0;
}
