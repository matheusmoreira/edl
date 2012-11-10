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

edl_status edl_library_create(edl_library ** library_reference) {
    edl_library * library = NULL;

    if (library_reference == NULL) { return EDL_NULL_POINTER_ERROR; }

    library = malloc(sizeof *library);
    if (library == NULL) { return EDL_MEMORY_ALLOCATION_ERROR; }

    library->name = library->error_message = NULL;
    library->native_handle = NULL;

    *library_reference = library;

    return EDL_LIBRARY_CREATED_SUCCESSFULLY;
}

edl_status edl_library_destroy(edl_library ** library_reference) {
    edl_library * library = NULL;

    if (library == NULL) { return EDL_NULL_POINTER_ERROR; }

    library = *library_reference;
    if (library == NULL) { return EDL_NOTHING_TO_DO; }

    edl_status status = edl_library_close(library);
    if (edl_status_is_failure(status)) { return status; }

    free(library);
    *library_reference = NULL;

    return EDL_LIBRARY_DESTROYED_SUCCESSFULLY;
}

edl_status edl_library_open(edl_library * library, const char * name) {
    void * handle = NULL;

    if (library == NULL) { return EDL_NULL_POINTER_ERROR; }
    /* name may be NULL */

    if (edl_library_is_open(library)) { return EDL_LIBRARY_ALREADY_OPENED_ERROR; }

    handle = edl_library_find_and_open(name);
    if (handle == NULL) {
        edl_library_set_error(library);
        return EDL_LIBRARY_SHARED_OBJECT_NOT_FOUND_ERROR;
    }

    library->name = name;
    library->native_handle = handle;

    return EDL_LIBRARY_OPENED_SUCCESSFULLY;
}

edl_status edl_library_close(edl_library * library) {
    edl_status status = EDL_LIBRARY_CLOSED_SUCCESSFULLY;

    if (library == NULL) { return EDL_NULL_POINTER_ERROR; }

    if (edl_library_is_open(library)) {
        status = edl_native_library_close(library->native_handle);

        if (status == EDL_LIBRARY_CLOSED_SUCCESSFULLY) {
            library->native_handle = NULL;
        } else {
            edl_library_set_error(library);
        }
    } else {
        status = EDL_LIBRARY_ALREADY_CLOSED;
    }

    return status;
}

edl_status edl_library_current(edl_library * library) {
    return edl_library_open(library, NULL);
}

edl_status edl_library_get_object(edl_library * library, const char * name, edl_object * object) {
    edl_object address = NULL;

    if (library == NULL || object == NULL) { return EDL_NOTHING_TO_DO; }
    if (edl_library_is_closed(library)) { return EDL_LIBRARY_CLOSED_ERROR; }

    address = edl_native_library_get_object(library->native_handle, name);
    if (address == NULL) {
        edl_library_set_error(library);
        return EDL_LIBRARY_OBJECT_NOT_FOUND_ERROR;
    }

    *object = address;

    return EDL_LIBRARY_OBJECT_FOUND;
}

edl_status edl_library_get_function(edl_library * library, const char * name, edl_function * function) {
    edl_function address = NULL;

    if (library == NULL || function == NULL) { return EDL_NOTHING_TO_DO; }
    if (edl_library_is_closed(library)) { return EDL_LIBRARY_CLOSED_ERROR; }

    address = edl_native_library_get_function(library->native_handle, name);
    if (address == NULL) {
        edl_library_set_error(library);
        return EDL_LIBRARY_FUNCTION_NOT_FOUND_ERROR;
    }

    *function = address;

    return EDL_LIBRARY_FUNCTION_FOUND;
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
