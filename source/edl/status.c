#include <edl/status.h>

/* edl_status interface implementation */

int edl_status_is_successful(edl_status_t status) {
    switch (status) {
        case EDL_SUCCESS:
        case EDL_CLOSED_SUCCESSFULLY:
            return 1;
        default:
            return 0;
    }
}

int edl_status_is_failure(edl_status_t status) {
    return !edl_status_is_successful(status);
}
