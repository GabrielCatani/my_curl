#include "my_curl.h"
#include "con_error.h"


struct hostent *get_host_info(char *domain) {
  struct hostent *host_info;

  //Check if valid domain
  host_info = gethostbyname(domain);
  if (!host_info) {
    host_error(h_errno);
    return NULL;
  }

  return host_info;
}

struct sockaddr_in *set_socket(struct hostent *host_info) {
  struct sockaddr_in *socket_info = NULL;
  struct in_addr **address_list;

  //Fill socket_info with host_info
  //TODO: Replace htons for my_htons
  if (host_info) {
    socket_info = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    address_list = (struct in_addr **) host_info->h_addr_list;
    socket_info->sin_family = AF_INET;
    socket_info->sin_port = htons(80);
    socket_info->sin_addr = *address_list[0];
    my_memset(socket_info->sin_zero, 0, sizeof(socket_info->sin_zero));
  }
  
  return socket_info;
}

int open_connection(struct sockaddr_in *socket_info) {
  int sockfd = 0;
  struct sockaddr_in socket_info_ptr;
  
  if (!socket_info) {
    return -1;
  }

  socket_info_ptr = *socket_info;
  //Create socket
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  
  //Create connection
  if (connect(sockfd,
	   (struct sockaddr *)&socket_info_ptr,
	      sizeof(socket_info_ptr)) == -1) {
    my_putstr("Connection failed", 1);
    close(sockfd);
    return -1;
  }
  
  //return valid socket
  return sockfd;
  //Caller has to close socket!!!
}

void close_connection(struct sockaddr_in *socket_info, int sockfd) {
  free(socket_info);
  close(sockfd);
}
