#include "my_curl.h"
#include "con_error.h"

int open_connection(char *domain) {
  int sockfd = 0;
  struct sockaddr_in socket_info;
  struct hostent *host_info;
  struct in_addr **address_list;

  //Check if valid domain
  host_info = gethostbyname(domain);
  if (!host_info) {
    host_error(h_errno);
    return -1;
  }

  //Fill socket_info with host_info
  //TODO: Replace htons for my_htons
  address_list = (struct in_addr **) host_info->h_addr_list;
  socket_info.sin_family = AF_INET;
  socket_info.sin_port = htons(80);
  socket_info.sin_addr = *address_list[0];
  my_memset(socket_info.sin_zero, 0, sizeof(socket_info.sin_zero));
  
  //Create socket
  sockfd = socket(PF_INET, SOCK_STREAM, 0);

  if (sockfd == -1) {
    my_putstr("Socket creation failed", 1);
    return -1;
  }
  /*
  //Create Bind to default port 80
  if (bind(sockfd,
	   (struct sockaddr *)&socket_info,
	   sizeof(struct sockaddr_in)) == -1) {
    my_putstr("Bind failed", 1);
    close(sockfd);
    return -1;
  }
  */
  //Create connection
  if (connect(sockfd,
	   (struct sockaddr *)&socket_info,
	   sizeof(socket_info)) == -1) {
    my_putstr("Connection failed", 1);
    close(sockfd);
    return -1;
  }  
  //return valid socket
  return sockfd;
  //Caller has to close socket!!!
}
