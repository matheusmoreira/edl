#include <stdlib.h>

#include <edl/platform/specifics.h>
#include <edl/library.h>
#include <edl/status.h>

struct edl_library {
    const char * name;
    void * native_handle;
    const char * error_message;
};

/* Helper function prototypes */

static void * edl_library_find_and_open(const char * name);

/* edl_library interface implementation */

edl_library_t * edl_library_new() {
    edl_library_t * library = malloc(sizeof *library);

    library->name = library->native_handle = library->error_message = NULL;

    return library;
}

edl_status_t edl_library_destroy(edl_library_t * library) {
    if (library == NULL) { return EDL_SUCCESS; }
    if (edl_library_close(library) == EDL_FAILURE) { return EDL_FAILURE; }
    free(library);
    return EDL_SUCCESS;
}

edl_status_t edl_library_open(edl_library_t * library, const char * name) {
    void * handle = NULL;

    if (library == NULL) { return EDL_FAILURE; }

    handle = edl_library_find_and_open(name);
    if (handle == NULL) {
        library->error_message = edl_native_last_error();
        return EDL_FAILURE;
    }

    library->name = name;
    library->native_handle = handle;

    return EDL_SUCCESS;
}

edl_status_t edl_library_current(edl_library_t * library) {
    return edl_library_open(library, NULL);
}

edl_status_t edl_library_close(edl_library_t * library) {
    edl_status_t status = EDL_CLOSED_SUCCESSFULLY;

    if (library != NULL && library->native_handle != NULL) {
        status = edl_native_close_library(library->native_handle);

        if (status == EDL_CLOSED_SUCCESSFULLY) {
            library->native_handle = NULL;
        } else {
            library->error_message = edl_native_last_error();
        }
    }

    return status;
}

void * edl_library_resolve_symbol(edl_library_t * library,
                                  const char * symbol) {
    return edl_native_resolve_symbol(library->native_handle, symbol);
}

const char * edl_library_last_error(edl_library_t * library) {
    return library->error_message;
}

/* Helper functions */

static void * edl_library_find_and_open(const char * name) {
    /* TODO: Try all possible extensions */
    return edl_native_open_library(name);
}
