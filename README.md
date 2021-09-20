# my_curl

## Introduction ##

my_curl is a program that emulates the curl tool - that is responsible to transfer data from or to a server. My_curl is a limited version, accepting only the http protocol.

## Usage ##

  Compiling
  ```
  make
  ```
  Execute
  ```
  ./my_curl http://www.columbia.edu/~fdc/sample.html
  ```
  Returns the resource available on the URL(HTML, JSON, etc)
  ```
  <!DOCTYPE HTML>
  <html lang="en">
  <head>
  [...]
  </html>  <!-- close the <html> begun above -->
  ```

## Program Overview and Components ##

  ### 1. Parse URL passed by the user

  Given the URL passed to my_curl, we must first identify if it's a valid format:
  ```
  http://www.columbia.edu/~fdc/sample.html

     http://    www.columbia        .edu             /~fdc/sample.html
  | Protocol | |  Domain    | | Top Level Domain |  |     Resource    |
  ```
  For my_curl:
  
  * **Protocol**: http:// (can be omitted)
  * **Domain**: name of the server on the internet, can have multiple parts, separated by '.'
  * **Top Level Domain(TLD)**: can be .com, .net, .org, etc.
  *  **Resource**: name of the resource (file, HTML page, JSON etc.). Can be ommited, which will normally point ou to home/index.html deppending on the server hosting the URL.

  ### 2. DNS Lookup
  
  With a valid URL, we procced to check if that Domain exists on the internet, and fetch it's IP - we need the IP, in order
  to build a socket, bind to a host port and make a connection with the server in the next steps. For that, we will be using:
  ```
  // For getting domain info.
  struct hostent *gethostbyname(const char *name);

  // hostent->h_addr_list has the list of the IP for the domain returned by gethostbyname()
  struct  hostent {
           char    *h_name;        /* official name of host */
           char    **h_aliases;    /* alias list */
           int     h_addrtype;     /* host address type */
           int     h_length;       /* length of address */
           char    **h_addr_list;  /* list of addresses from name server */
   };
  ```

  ### 3. Set up connection elements
  
  In order to make a proper connection, we must first create a socket - which is basically a file descriptor, that is
  used to send and receive data from a connection. With a valid socket created, we bind it to a port on the host machine,
  and finally create a connection.

  **Creating a Socket**
  ```
  int  socket(int domain, int type, int protocol);

  // Struct with socket info, that will be passed to bind() and connect()
  struct sockaddr_in {
          sa_family_t    sin_family; /* address family: AF_INET */
          in_port_t      sin_port;   /* port in network byte order */
          struct in_addr sin_addr;   /* internet address */
  };

  /* Internet address */
  struct in_addr {
           uint32_t       s_addr;     /* address in network byte order */
  };

  ```

 **Bind and Connect**
   if both returned 0, bind and connection were successeful, and we are ready to interact with the connected server.
 ```
 // struct sockaddr_in can be casted to struct sockaddr

 int bind(int socket, const struct sockaddr *address,
         socklen_t address_len);

 //
 int  connect(int socket, const struct sockaddr *address,
         socklen_t address_len);
 ```

  ### 4. Prelude to a request
  
  With steps 3, we can immeditely start sending and receiving data to the server. But, in order for the server know exactly
  what data we are asking for, and how to send that data for us, we must follow certain rules. Does rules are determined by the protocol
  used by the server. In my_curl, we be using http.

  To send an "http message"(request) we must create an HTTP header, that will be send to the server. This header, has some information
  about the server that can be overdetailed or simple, depending on the user necessity and server configuration. One simple http header
  example:
    ```
    GET / HTTP/1.1 
    Host: www.columbia.edu

    ```
    
    **HTTP components**
    ```
    [Method] [Resource] [HTTP version]
    [...
    Request Fields
    ...]
    \r\n
    ```

  ### 5. Making a Request, receiving a Response.

  After creating a socket, binding it to a port, making the connection to the server, and creating an HTTP Header, now it's just a matter of
  sending the http header to the server. Thats just a matter of writing the header to the file descriptor, created by the socket function.

  **Http Request**
  ```
  int sockfd = socket();
  char *http_header = "
    GET / HTTP/1.1
    Host: www.columbia.edu
    \r\n";

  write(sockfd, http_header, strlen(http_header));
  ```

  After that, it's just a matter of reading from the same file descriptor, to get access to the data sent by the server, responding to
  the request made.

  As the request, the response also comes with an http header, with information like if the request was successeful, the size of the response
  the type of data, etc. So before reading and outputting the data directly to stdout, it's important to Parse and extract info. from the
  response header.