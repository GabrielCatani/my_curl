#include "my_string.h"
#include "lexer_parser.h"

//Check whether the character is permitted in protocol string
int is_protocol_char(int c)
{
    return (!my_isalpha(c) && '+' != c && '-' != c && '.' != c) ? 0 : 1;
}

void http_parsed_url_free(parsed_url *purl)
{
    if (NULL != purl)
    {
        if (NULL != purl->protocol)
            free(purl->protocol);
        if (NULL != purl->host)
            free(purl->host);
        if (NULL != purl->port)
            free(purl->port);
        if (NULL != purl->path)
            free(purl->path);
        if (NULL != purl->query)
            free(purl->query);
        if (NULL != purl->fragment)
            free(purl->fragment);
        if (NULL != purl->username)
            free(purl->username);
        if (NULL != purl->password)
            free(purl->password);
        free(purl);
    }
}

//Allocate the parsed url storage */
parsed_url *purl_initializer(void)
{
    parsed_url *purl;
    purl = malloc(sizeof(parsed_url));

    if (NULL == purl)
        return NULL;

    purl->protocol = NULL;
    purl->host = NULL;
    purl->port = NULL;
    purl->path = NULL;
    purl->query = NULL;
    purl->fragment = NULL;
    purl->username = NULL;
    purl->password = NULL;

    return purl;
}

parsed_url *parse_url(char *url)
{
    parsed_url *purl = purl_initializer();
    char *curstr = my_strdup(url);
    char *tmpstr = my_strchr(curstr, ':');
    int len = tmpstr - curstr;
    int userpass_flag;
    int bracket_flag;

    //default case, we will try HTTP
    if (tmpstr == NULL || my_strcmp(tmpstr, "HTTP") == 0 || my_strcmp(tmpstr, "http") == 0)
    {
        purl->protocol = my_strdup("HTTP");
    }
    //case that protocol is different from HTTP
    else if (my_strcmp(tmpstr, "HTTP") != 0 || my_strcmp(tmpstr, "http") != 0)
    {
        http_parsed_url_free(purl);
        return NULL;
    }

    /* Check restrictions */
    for (int i = 0; i < len; i++)
    {
        if (!_is_protocol_char(curstr[i]))
        {
            /* Invalid format */
            http_parsed_url_free(purl);
            return NULL;
        }
    }
    /* Copy the protocol to the storage */
    purl->protocol = malloc(sizeof(char) * (len + 1));
    if (NULL == purl->protocol)
    {
        http_parsed_url_free(purl);
        return NULL;
    }
    (void)strncpy(purl->protocol, curstr, len);
    purl->protocol[len] = '\0';
    /* Make the character to lower if it is upper case. */
    for (int i = 0; i < len; i++)
    {
        purl->protocol[i] = tolower(purl->protocol[i]);
    }
    /* Skip ':' */
    tmpstr++;
    curstr = tmpstr;

    /*
     * //<user>:<password>@<host>:<port>/<url-path>
     * Any ":", "@" and "/" must be encoded.
     */
    /* Eat "//" */
    for (int i = 0; i < 2; i++)
    {
        if ('/' != *curstr)
        {
            http_parsed_url_free(purl);
            return NULL;
        }
        curstr++;
    }

    /* Check if the user (and password) are specified. */
    userpass_flag = 0;
    tmpstr = curstr;
    while ('\0' != *tmpstr)
    {
        if ('@' == *tmpstr)
        {
            /* Username and password are specified */
            userpass_flag = 1;
            break;
        }
        else if ('/' == *tmpstr)
        {
            /* End of <host>:<port> specification */
            userpass_flag = 0;
            break;
        }
        tmpstr++;
    }

    /* User and password specification */
    tmpstr = curstr;
    if (userpass_flag)
    {
        /* Read username */
        while ('\0' != *tmpstr && ':' != *tmpstr && '@' != *tmpstr)
        {
            tmpstr++;
        }
        len = tmpstr - curstr;
        purl->username = malloc(sizeof(char) * (len + 1));
        if (NULL == purl->username)
        {
            http_parsed_url_free(purl);
            return NULL;
        }
        (void)strncpy(purl->username, curstr, len);
        purl->username[len] = '\0';
        /* Proceed current pointer */
        curstr = tmpstr;
        if (':' == *curstr)
        {
            /* Skip ':' */
            curstr++;
            /* Read password */
            tmpstr = curstr;
            while ('\0' != *tmpstr && '@' != *tmpstr)
            {
                tmpstr++;
            }
            len = tmpstr - curstr;
            purl->password = malloc(sizeof(char) * (len + 1));
            if (NULL == purl->password)
            {
                http_parsed_url_free(purl);
                return NULL;
            }
            (void)strncpy(purl->password, curstr, len);
            purl->password[len] = '\0';
            curstr = tmpstr;
        }
        /* Skip '@' */
        if ('@' != *curstr)
        {
            http_parsed_url_free(purl);
            return NULL;
        }
        curstr++;
    }

    if ('[' == *curstr)
    {
        bracket_flag = 1;
    }
    else
    {
        bracket_flag = 0;
    }
    /* Proceed on by delimiters with reading host */
    tmpstr = curstr;
    while ('\0' != *tmpstr)
    {
        if (bracket_flag && ']' == *tmpstr)
        {
            /* End of IPv6 address. */
            tmpstr++;
            break;
        }
        else if (!bracket_flag && (':' == *tmpstr || '/' == *tmpstr))
        {
            /* Port number is specified. */
            break;
        }
        tmpstr++;
    }
    len = tmpstr - curstr;
    purl->host = malloc(sizeof(char) * (len + 1));
    if (NULL == purl->host || len <= 0)
    {
        http_parsed_url_free(purl);
        return NULL;
    }
    (void)strncpy(purl->host, curstr, len);
    purl->host[len] = '\0';
    curstr = tmpstr;

    /* Is port number specified? */
    if (':' == *curstr)
    {
        curstr++;
        /* Read port number */
        tmpstr = curstr;
        while ('\0' != *tmpstr && '/' != *tmpstr)
        {
            tmpstr++;
        }
        len = tmpstr - curstr;
        purl->port = malloc(sizeof(char) * (len + 1));
        if (NULL == purl->port)
        {
            http_parsed_url_free(purl);
            return NULL;
        }
        (void)strncpy(purl->port, curstr, len);
        purl->port[len] = '\0';
        curstr = tmpstr;
    }

    /* End of the string */
    if ('\0' == *curstr)
    {
        return purl;
    }

    /* Skip '/' */
    if ('/' != *curstr)
    {
        http_parsed_url_free(purl);
        return NULL;
    }
    curstr++;

    /* Parse path */
    tmpstr = curstr;
    while ('\0' != *tmpstr && '#' != *tmpstr && '?' != *tmpstr)
    {
        tmpstr++;
    }
    len = tmpstr - curstr;
    purl->path = malloc(sizeof(char) * (len + 1));
    if (NULL == purl->path)
    {
        http_parsed_url_free(purl);
        return NULL;
    }
    (void)strncpy(purl->path, curstr, len);
    purl->path[len] = '\0';
    curstr = tmpstr;

    /* Is query specified? */
    if ('?' == *curstr)
    {
        /* Skip '?' */
        curstr++;
        /* Read query */
        tmpstr = curstr;
        while ('\0' != *tmpstr && '#' != *tmpstr)
        {
            tmpstr++;
        }
        len = tmpstr - curstr;
        purl->query = malloc(sizeof(char) * (len + 1));
        if (NULL == purl->query)
        {
            http_parsed_url_free(purl);
            return NULL;
        }
        (void)strncpy(purl->query, curstr, len);
        purl->query[len] = '\0';
        curstr = tmpstr;
    }

    /* Is fragment specified? */
    if ('#' == *curstr)
    {
        /* Skip '#' */
        curstr++;
        /* Read fragment */
        tmpstr = curstr;
        while ('\0' != *tmpstr)
        {
            tmpstr++;
        }
        len = tmpstr - curstr;
        purl->fragment = malloc(sizeof(char) * (len + 1));
        if (NULL == purl->fragment)
        {
            http_parsed_url_free(purl);
            return NULL;
        }
        (void)strncpy(purl->fragment, curstr, len);
        purl->fragment[len] = '\0';
        curstr = tmpstr;
    }

    return purl;
}

/* Function inputs and outputs

//input -> www.example.com
//  lexeme extraction
//  parse lexemes to see if they are valid
//  http request string
//output -> char *http_header = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
//  every line is sepparated by \r\n
//  GET / is default to main page

*/