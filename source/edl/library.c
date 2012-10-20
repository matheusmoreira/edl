#include <stdlib.h>

#include <edl/library.h>

#include <edl/platform/specifics.h>
#include <edl/function.h>
#include <edl/object.h>
#include <edl/status.h>

struct edl_library {
    const char * name;
    void * native_handle;
    const char * error_message;
};

/* Helper function prototypes */

static void * edl_library_find_and_open(const char * name);
static void edl_library_set_error(edl_library * library);

/* edl_library interface implementation */

edl_library * edl_library_create() {
    edl_library * library = NULL;

    library = malloc(sizeof *library);
    if (library == NULL) { return NULL; }

    library->name = library->native_handle = library->error_message = NULL;

    return library;
}

edl_status edl_library_destroy(edl_library * library) {
    if (library == NULL) { return EDL_SUCCESS; } else {
        edl_status status = edl_library_close(library);
        if (edl_status_is_failure(status)) { return status; }
    }

    free(library);

    return EDL_DESTROYED_SUCCESSFULLY;
}

edl_status edl_library_open(edl_library * library, const char * name) {
    void * handle = NULL;

    if (library == NULL) { return EDL_FAILURE; }

    handle = edl_library_find_and_open(name);
    if (handle == NULL) {
        edl_library_set_error(library);
        return EDL_FAILURE;
    }

    library->name = name;
    library->native_handle = handle;

    return EDL_SUCCESS;
}

edl_status edl_library_current(edl_library * library) {
    return edl_library_open(library, NULL);
}

edl_status edl_library_close(edl_library * library) {
    edl_status status = EDL_CLOSED_SUCCESSFULLY;

    if (edl_library_is_open(library)) {
        status = edl_native_library_close(library->native_handle);

        if (status == EDL_CLOSED_SUCCESSFULLY) {
            library->native_handle = NULL;
        } else {
            edl_library_set_error(library);
        }
    }

    return status;
}

edl_object edl_library_get_object(edl_library * library,
                                          const char * name) {
    edl_object object = NULL;

    object = edl_native_library_get_object(library->native_handle, name);
    if (object == NULL) { edl_library_set_error(library); }

    return object;
}

edl_function edl_library_get_function(edl_library * library,
                                              const char * name) {
    edl_function function = NULL;

    function = edl_native_library_get_function(library->native_handle, name);
    if (function == NULL) { edl_library_set_error(library); }

    return function;
}

int edl_library_is_open(edl_library * library) {
    if (library == NULL) { return 0; }
    return library->native_handle != NULL;
}

int edl_library_is_closed(edl_library * library) {
    return !edl_library_is_open(library);
}

const char * edl_library_last_error(edl_library * library) {
    if (library == NULL) { return NULL; }
    return library->error_message;
}

/* Helper functions */

static void * edl_library_find_and_open(const char * name) {
    /* TODO: Try all possible extensions */
    return edl_native_library_open(name);
}

static void edl_library_set_error(edl_library * library) {
    library->error_message = edl_native_library_last_error();
}
