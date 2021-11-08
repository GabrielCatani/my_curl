#include "con_error.h"

void host_error(int err_nbr) {

  switch(err_nbr) {
    case HOST_NOT_FOUND:
      my_putstr("Could not resolve host: ", 0);
      break;
    case TRY_AGAIN:
      printf("Try Again\n");
      break;
    case NO_RECOVERY:
      printf("No Recovery\n");
      break;
    case NO_DATA:
      printf("No Data\n");
      break;


  }
}
