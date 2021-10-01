#ifndef lexer_parser_H
#define lexer_parser_H
typedef struct parsed_url
{
    char *scheme;   /* mandatory */
    char *host;     /* mandatory */
    char *port;     /* optional */
    char *path;     /* optional */
    char *query;    /* optional */
    char *fragment; /* optional */
    char *username; /* optional */
    char *password; /* optional */
} parsed_url;

parsed_url *parse_url(const char *);
void parsed_url_free(struct parsed_url *);

#endif