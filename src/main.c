#include "my_curl.h"

int main(void) {

  //Test open_connection
  if (open_connection("www.google.com")) {
    my_putstr("Connection Established!", 1);
  }
  if (open_connection("not_valid_host")) {
    my_putstr("Failed Connection!", 1);
  }
  return 0;
}
