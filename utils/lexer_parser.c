#include "my_string.h"
#include "lexer_parser.h"

//input -> www.example.com
//  lexeme extraction
//  parse lexemes to see if they are valid
//  http request string
//output -> char *http_header = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
//  every line is sepparated by \r\n
//  GET / is default to main page
