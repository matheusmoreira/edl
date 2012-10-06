#ifndef EDL_STATUS_HEADER
#define EDL_STATUS_HEADER

typedef enum edl_status {
    EDL_SUCCESS,
    EDL_FAILURE,
    EDL_CLOSED_SUCCESSFULLY,
    EDL_DESTROYED_SUCCESSFULLY
} edl_status_t;

extern int edl_status_is_successful(edl_status_t status);
extern int edl_status_is_failure(edl_status_t status);

#endif /* EDL_STATUS_HEADER */
