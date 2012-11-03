#ifndef EDL_STATUS_HEADER
#define EDL_STATUS_HEADER

typedef enum edl_status {
    EDL_SUCCESS,
    EDL_FAILURE,

    EDL_API_INITIALIZED_SUCCESSFULLY,

    EDL_CLOSED_SUCCESSFULLY,
    EDL_DESTROYED_SUCCESSFULLY,

    EDL_API_LIBRARY_CLOSED_ERROR,
    EDL_API_OBJECT_INITIALIZATION_ERROR,
} edl_status;

extern int edl_status_is_successful(edl_status status);
extern int edl_status_is_failure(edl_status status);
extern const char * edl_status_name(edl_status status);

#endif /* EDL_STATUS_HEADER */
