#ifndef __SIMPLE_PARSER_H__
#define __SIMPLE_PARSER_H__
#include <stdio.h>
#include "my_string.h"
typedef struct host_info host_info;
struct host_info {
  char *host;
  char *resource;
  char *request;
};
void initialize_host_info(struct host_info **h_info);
void destroy_host_info(struct host_info **h_info);
struct host_info *parse_usr_url(char *usr_input);
char *form_request(char *host, char *resource);
#endif
