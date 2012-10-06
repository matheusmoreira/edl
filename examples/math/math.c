#include <stdio.h>
#include <stdlib.h>

#include <edl.h>

typedef double (*pow_function_t)(double, double);

int main(int argc, char ** argv) {
    const char * path_to_library = "libm.so";
    edl_library_t * math_library = NULL;
    edl_status_t status;
    pow_function_t pow;
    double base = 2, exponent = 16;

    if (argc >= 3) {
        base = atof(argv[1]);
        exponent = atof(argv[2]);

        if (argc >= 4) {
            path_to_library = argv[3];
        }
    }

    math_library = edl_library_new();
    if (math_library == NULL) {
        fprintf(stderr, "Could not allocate memory for math library\n");
        exit(1);
    }

    status = edl_library_open(math_library, path_to_library);
    if (status != EDL_SUCCESS) {
        fprintf(stderr,
                "Could not open math library - %s\n", edl_library_last_error());
        exit(2);
    }

    pow = (pow_function_t) edl_library_resolve_symbol(math_library, "pow");
    if (pow == NULL) {
        fprintf(stderr,
                "Symbol resolution failed - %s\n", edl_library_last_error());
        exit(3);
    }

    printf("%f^%f = %f\n", base, exponent, pow(base, exponent));

    status = edl_library_destroy(math_library);
    if(status != EDL_SUCCESS) {
        fprintf(stderr,
                "Could not destroy the math library - %s\n",
                edl_library_last_error());
        exit(4);
    }

    return 0;
}
