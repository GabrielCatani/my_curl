#ifndef __HTTP_COM_H__
#define __HTTP_COM_H__
char **get_response_header(int sockfd);
void request(int sockfd, char *http_header);
#define BUFFER_SIZE 512
#endif
