#include <stdio.h>
#include <stdlib.h>

#include <edl.h>

typedef double (*pow_function)(double, double);

int main(int argc, char ** argv) {
    const char * path_to_library = "libm.so";
    edl_library * math_library = NULL;
    edl_status status;
    pow_function pow;
    double base = 2, exponent = 16;

    if (argc >= 3) {
        base = atof(argv[1]);
        exponent = atof(argv[2]);

        if (argc >= 4) {
            path_to_library = argv[3];
        }
    }

    printf("Base: %f" "\n" "Exponent: %f" "\n" "Math library: %s" "\n",
           base, exponent, path_to_library);

    printf("Creating math library...");
    math_library = edl_library_create();
    if (math_library == NULL) {
        fprintf(stderr, "\n" "Could not allocate memory for math library" "\n");
        exit(1);
    } else { printf(" created" "\n"); }

    printf("Opening \"%s\"... ", path_to_library);
    status = edl_library_open(math_library, path_to_library);
    printf("%s" "\n", edl_status_name(status));
    if (edl_status_is_failure(status)) {
        fprintf(stderr,
                "Could not open math library - %s" "\n",
                edl_library_last_error(math_library));
        exit(2);
    }

    printf("Acquiring \"pow\" function...");
    pow = (pow_function) edl_library_get_function(math_library, "pow");
    if (pow == NULL) {
        fprintf(stderr,
                "\n" "Could not find function - %s" "\n",
                edl_library_last_error(math_library));
        exit(3);
    } else { printf(" acquired\n"); }

    printf("\n\t" "%f ^ %f = %f" "\n\n",
           base, exponent, pow(base, exponent));

    printf("Destroying math library... ");
    status = edl_library_destroy(math_library);
    printf("%s" "\n", edl_status_name(status));
    if(edl_status_is_failure(status)) {
        fprintf(stderr,
                "Could not destroy the math library - %s" "\n",
                edl_library_last_error(math_library));
        exit(4);
    }

    return 0;
}
