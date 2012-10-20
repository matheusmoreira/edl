#include <edl/status.h>

/* edl_status interface implementation */

int edl_status_is_successful(edl_status status) {
    switch (status) {
        case EDL_SUCCESS:
        case EDL_CLOSED_SUCCESSFULLY:
        case EDL_DESTROYED_SUCCESSFULLY:
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
        NAME(EDL_FAILURE);
        NAME(EDL_CLOSED_SUCCESSFULLY);
        NAME(EDL_DESTROYED_SUCCESSFULLY);
    }
}

#undef NAME
