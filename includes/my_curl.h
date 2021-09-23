#ifndef __MY_CURL_H__
#define __MY_CURL_H__
//socket, bind and connect
#include <sys/socket.h>
#include <sys/types.h>
//gethostbyname() -> DNS Lookup
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_string.h"
#include "http_com.h"
//Connection
int open_connection(struct sockaddr_in *socket_info);
void close_connection(struct sockaddr_in *socket_info, int sockfd);
struct hostent *get_host_info(char *domain);
struct sockaddr_in *set_socket(struct hostent *host_info);
#endif
