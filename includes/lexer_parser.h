#ifndef lexer_parser_H
#define lexer_parser_H

#include <stdio.h>
typedef struct parsed_url
{
    char *protocol; /* mandatory */
    char *host;     /* mandatory */
    char *port;     /* optional */
    char *path;     /* optional */
    char *query;    /* optional */
    char *fragment; /* optional */
    char *username; /* optional */
    char *password; /* optional */
} parsed_url;

parsed_url *parse_url(char *url);
parsed_url *purl_initializer(void);
int is_protocol_char(int c);
void http_parsed_url_free(parsed_url *purl);
void protocol_checker(char *tmpstr, parsed_url *purl, char *url);
int restriction_url_checker(char *curstr);

#endif