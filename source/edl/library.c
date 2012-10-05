#include <stdlib.h>

#include <edl/platform/specifics.h>
#include <edl/library.h>
#include <edl/status.h>

struct edl_library {
    const char * name;
    void * native_handle;
};

static void * edl_library_find_and_open(const char * name);

edl_library_t * edl_library_new() {
    return malloc(sizeof(edl_library_t));
}

void edl_library_destroy(edl_library_t * library) {
    if (library == NULL) { return; }
    free(library);
}

edl_library_t * edl_library_open(const char * name) {
    edl_library_t * library = NULL;
    void * handle = edl_library_find_and_open(name);

    if (handle == NULL) { return NULL; }

    library = edl_library_new();
    if (library == NULL) { return NULL; }

    library->name = name;
    library->native_handle = handle;
    return library;
}

edl_library_t * edl_main_library() {
    return edl_library_open(NULL);
}

edl_status_t edl_library_close(edl_library_t * library) {
    edl_status_t status = EDL_SUCCESS;

    if (library != NULL && library->native_handle != NULL) {
        status = edl_native_close_library(library->native_handle);
        library->native_handle = NULL;
    }

    return status;
}

void * edl_library_resolve_symbol(edl_library_t * library,
                                  const char * symbol) {
    return edl_native_resolve_symbol(library->native_handle, symbol);
}

const char * edl_last_error() {
    return edl_native_last_error();
}

/* Helper functions */

static void * edl_library_find_and_open(const char * name) {
    /* TODO: Try all possible extensions */
    return edl_native_open_library(name);
}
