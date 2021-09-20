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
//Connection
int open_connection(char *domain);
#endif
