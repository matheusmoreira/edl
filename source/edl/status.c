#include <edl/status.h>

/* edl_status interface implementation */

int edl_status_is_successful(edl_status status) {
    switch (status) {
        case EDL_SUCCESS:

        case EDL_NOTHING_TO_DO:

        case EDL_API_INITIALIZED_SUCCESSFULLY:

        case EDL_LIBRARY_CREATED_SUCCESSFULLY:
        case EDL_LIBRARY_DESTROYED_SUCCESSFULLY:
        case EDL_LIBRARY_OPENED_SUCCESSFULLY:
        case EDL_LIBRARY_CLOSED_SUCCESSFULLY:
        case EDL_LIBRARY_ALREADY_CLOSED:
        case EDL_LIBRARY_OBJECT_FOUND:
        case EDL_LIBRARY_FUNCTION_FOUND:

            return 1;

        default:

            return 0;
    }
}

int edl_status_is_failure(edl_status status) {
    return !edl_status_is_successful(status);
}

#define NAME(status) case status: return #status; break

const char * edl_status_name(edl_status status) {
    switch (status) {
        NAME(EDL_SUCCESS);

        NAME(EDL_NOTHING_TO_DO);

        NAME(EDL_API_INITIALIZED_SUCCESSFULLY);

        NAME(EDL_LIBRARY_CREATED_SUCCESSFULLY);
        NAME(EDL_LIBRARY_DESTROYED_SUCCESSFULLY);
        NAME(EDL_LIBRARY_OPENED_SUCCESSFULLY);
        NAME(EDL_LIBRARY_CLOSED_SUCCESSFULLY);
        NAME(EDL_LIBRARY_ALREADY_CLOSED);
        NAME(EDL_LIBRARY_OBJECT_FOUND);
        NAME(EDL_LIBRARY_FUNCTION_FOUND);

        NAME(EDL_FAILURE);

        NAME(EDL_NULL_POINTER_ERROR);
        NAME(EDL_MEMORY_ALLOCATION_ERROR);

        NAME(EDL_API_LIBRARY_CLOSED_ERROR);
        NAME(EDL_API_OBJECT_INITIALIZATION_ERROR);
        NAME(EDL_API_FUNCTION_INITIALIZATION_ERROR);

        NAME(EDL_LIBRARY_CLOSED_ERROR);
        NAME(EDL_LIBRARY_SHARED_OBJECT_NOT_FOUND_ERROR);
        NAME(EDL_LIBRARY_OBJECT_NOT_FOUND_ERROR);
        NAME(EDL_LIBRARY_FUNCTION_NOT_FOUND_ERROR);
    }
}

#undef NAME
