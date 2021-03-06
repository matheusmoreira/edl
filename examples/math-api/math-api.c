#include <stdlib.h>
#include <stdio.h>

#include <edl.h>

typedef double (*trigonometric_function)(double);

trigonometric_function sine, cosine, tangent;

edl_api trigonometry_api = {
    .objects = NULL, .functions = (edl_api_function[]) {
        { "sin", (edl_function *) &sine    },
        { "cos", (edl_function *) &cosine  },
        { "tan", (edl_function *) &tangent },
        { 0 }
    }
};

void destroy(edl_library ** library);

int main(int argc, char ** argv) {
    const char * path_to_library = "libm.so";
    edl_library * math_library = NULL;
    edl_status status;
    double radians = 3.141593; /* π ≈ 3.141593 */

    if (argc >= 2) {
        radians = atof(argv[1]);

        if (argc >= 3) {
            path_to_library = argv[2];
        }
    }

    printf("Angle in radians: %f" "\n" "Math library: %s" "\n",
           radians, path_to_library);

    printf("Creating math library... ");
    status = edl_library_create(&math_library);
    printf("%s" "\n", edl_status_name(status));
    if (edl_status_is_failure(status)) {
        printf("\n" "Could not create math library" "\n");
        destroy(&math_library);
        exit(1);
    }

    printf("Opening \"%s\"... ", path_to_library);
    status = edl_library_open(math_library, path_to_library);
    printf("%s" "\n", edl_status_name(status));
    if (edl_status_is_failure(status)) {
        printf("Could not open math library - %s" "\n",
               edl_library_last_error(math_library));
        destroy(&math_library);
        exit(2);
    }

    printf("Initializing trigonometry API... ");
    status = edl_api_initialize(&trigonometry_api, math_library);
    printf("%s" "\n", edl_status_name(status));
    if (edl_status_is_failure(status)) {
        printf("\n" "Could not find object or function - %s" "\n",
               edl_library_last_error(math_library));
        destroy(&math_library);
        exit(3);
    }

    printf("\n\t" "sin(%f) = %f",        radians, sine(radians));
    printf("\n\t" "cos(%f) = %f",        radians, cosine(radians));
    printf("\n\t" "tan(%f) = %f" "\n\n", radians, tangent(radians));

    destroy(&math_library);

    return 0;
}

void destroy(edl_library ** library) {
    edl_status status = EDL_FAILURE;

    printf("Destroying math library... ");
    status = edl_library_destroy(library);
    printf("%s" "\n", edl_status_name(status));

    if(edl_status_is_failure(status)) {
        printf("Could not destroy the math library - %s" "\n",
               edl_library_last_error(*library));
        exit(-1);
    }
}
