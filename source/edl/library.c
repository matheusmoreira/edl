#include <stdlib.h>

#include <edl/library.h>
#include <edl/platform/specifics.h>

static void * edl_find_and_open_library(const char * name);

edl_library_t * edl_open_library(const char * name) {
    edl_library_t * library = NULL;
    void * handle = edl_find_and_open_library(name);

    if (handle == NULL) { return NULL; }

    library = malloc(sizeof *library);
    if (library == NULL) { /* malloc error */ return NULL; }

    library->name = name;
    library->native_handle = handle;
    return library;
}

edl_library_t * edl_main_library() {
    return edl_open_library(NULL);
}

int edl_close_library(edl_library_t * library) {
    return edl_native_close_library(library->native_handle);
}

void * edl_resolve_symbol(edl_library_t * library, const char * symbol) {
    return edl_native_resolve_symbol(library->native_handle, symbol);
}

const char * edl_last_error() {
    return edl_native_last_error();
}

/* Helper functions */

static void * edl_find_and_open_library(const char * name) {
    /* TODO: Try all possible extensions */
    return edl_native_open_library(name);
}
