#include <stdlib.h>
#include <stdio.h>

#include <edl.h>

void (*function)(int);
int * integer;

edl_api api = {

    .objects = (edl_api_object[]) {
        { "exposed_integer", (edl_object *) &integer }, NULL
    },

    .functions = (edl_api_function[]) {
        { "exposed_function", (edl_function *) &function }, NULL
    }

};

int main(int argc, char ** argv) {
    const char * path_to_library = "library/libapi_example.so";
    edl_library * library = NULL;
    edl_status status = EDL_FAILURE;

    if (argc >= 2) { path_to_library = argv[1]; }

    printf("Library: %s" "\n", path_to_library);

    printf("Creating library...");
    library = edl_library_create();
    if (library == NULL) {
        fprintf(stderr, "\n" "Could not allocate memory for library" "\n");
        exit(1);
    } else { printf(" created" "\n"); }

    printf("Opening \"%s\"... ", path_to_library);
    status = edl_library_open(library, path_to_library);
    printf("%s" "\n", edl_status_name(status));
    if (edl_status_is_failure(status)) {
        fprintf(stderr,
                "Could not open library - %s" "\n",
                edl_library_last_error(library));
        exit(2);
    }

    printf("Initializing API... ");
    status = edl_api_initialize(&api, library);
    printf("%s" "\n", edl_status_name(status));
    if (edl_status_is_failure(status)) {
        fprintf(stderr,
                "\n" "Could not find object or function - %s" "\n",
                edl_library_last_error(library));
        exit(3);
    }

    printf("Calling function with the library data..." "\n\n");

    function(*integer);

    printf("\n");

    printf("Destroying library... ");
    status = edl_library_destroy(library);
    printf("%s" "\n", edl_status_name(status));
    if(edl_status_is_failure(status)) {
        fprintf(stderr,
                "Could not destroy the library - %s" "\n",
                edl_library_last_error(library));
        exit(4);
    }

    return 0;
}
