#include <stdio.h>
#include <stdlib.h>

#include <edl.h>

typedef double (*pow_function_t)(double, double);

int main(int argc, char ** argv) {
    edl_library_t * math_library = edl_library_new();
    edl_status_t status;
    pow_function_t pow;
    double base = 2, exponent = 16;

    if (argc == 3) { base = atof(argv[1]); exponent = atof(argv[2]); }

    status = edl_library_open(math_library, "libm.so");
    if (status != EDL_SUCCESS) {
        fprintf(stderr, "%s\n", edl_library_last_error());
        exit(1);
    }

    pow = (pow_function_t) edl_library_resolve_symbol(math_library, "pow");
    if (pow == NULL) {
        fprintf(stderr, "%s\n", edl_library_last_error());
        exit(2);
    }

    printf("%f ^ %f = %f\n", base, exponent, pow(base, exponent));

    status = edl_library_close(math_library);
    if(status != EDL_SUCCESS) {
        fprintf(stderr, "%s\n", edl_library_last_error());
        exit(3);
    }

    edl_library_destroy(math_library);

    return 0;
}
