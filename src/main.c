#include "my_curl.h"

int main(void) {

  //Test open_connection
  struct sockaddr_in *socket_info = NULL;
  int sockfd = 0;
  socket_info = set_socket(get_host_info("www.google.com"));

  sockfd = open_connection(socket_info);
  if (sockfd > 2) {
    my_putstr("Connected to ", 0);
    my_putstr("Google", 1);
  }
  close_connection(socket_info, sockfd);

  sockfd = 0;
  socket_info = set_socket(get_host_info("not_valid_URL"));

  sockfd = open_connection(socket_info);

  close_connection(socket_info, sockfd);  

  return 0;
}
