#include <stdio.h>
#include <stdlib.h>

#include <edl.h>

int main(int argc, char ** argv) {
    edl_library_t * math_library = NULL;
    const char * error = NULL;
    double (*pow)(double, double);

    math_library = edl_open_library("libm.so");
    if (math_library == NULL) {
        fprintf(stderr, "%s\n", edl_last_error());
        exit(1);
    }

    pow = edl_resolve_symbol(math_library, "pow");
    error = edl_last_error();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(2);
    }

    printf("%f\n", pow(2.0, 2.0));

    if(edl_close_library(math_library) != 0) {
        fprintf(stderr, "%s\n", edl_last_error());
        exit(3);
    }

    edl_library_destroy(math_library);

    return 0;
}
