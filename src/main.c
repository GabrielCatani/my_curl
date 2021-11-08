#include "my_curl.h"

//$> my_curl "www.whatever.com"
int main(int argc, char **argv)
{
  //parsed_url *purl; = purl_initializer();
  if (argc != 2) {
    my_putstr("usage: my_curl [url]", 1);
    return 1;
  }
  //purl = parse_url("http:www.google.com");
  
  struct sockaddr_in *socket_info = NULL;
  http_response *http_res = NULL;
  int sockfd = 0;
  struct host_info *h_info = parse_usr_url(argv[1]);

  socket_info = set_socket(get_host_info(h_info->host));
  sockfd = open_connection(socket_info);

  if (sockfd > 2)
  {
    request(sockfd, h_info->request);
    http_res = get_http_response(sockfd);
    get_response_and_show(sockfd, http_res);
    destroy_http_response(&http_res);
  }

  close_connection(socket_info, sockfd);
  destroy_host_info(&h_info);
  return 0;
}
