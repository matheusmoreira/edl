#include "api_example.h"

#include <stdio.h>

int exposed_integer = 0xCAFEBABE;

void exposed_function(int given_integer) {
    printf("\t" "The given integer is 0x%X."                           "\n"
           "\t" "The value of the library\'s exposed integer is 0x%X." "\n",
           given_integer, exposed_integer);
}
