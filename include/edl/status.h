/**
 * @file
 *
 * Defines the `edl_api` enumeration, enumerates all possible function statuses
 * and declares related functions.
 */

#ifndef EDL_STATUS_HEADER
#define EDL_STATUS_HEADER

/**
 * @brief Enumeration of all possible function statuses.
 *
 * `edl_status` represents all possible success or error states that functions
 * may assume.
 */
typedef enum edl_status {
    EDL_SUCCESS,

    EDL_NOTHING_TO_DO,

    EDL_API_INITIALIZED_SUCCESSFULLY,

    EDL_LIBRARY_CLOSED_SUCCESSFULLY,
    EDL_LIBRARY_DESTROYED_SUCCESSFULLY,

    EDL_FAILURE,

    EDL_API_LIBRARY_NOT_GIVEN_ERROR,
    EDL_API_LIBRARY_CLOSED_ERROR,
    EDL_API_OBJECT_INITIALIZATION_ERROR,
    EDL_API_FUNCTION_INITIALIZATION_ERROR
} edl_status;

/**
 * Determines whether the given status is successful.
 *
 * @param [in] status The status to test.
 * @return Non-zero if successful, `0` otherwise.
 */
extern int edl_status_is_successful(edl_status status);

/**
 * Determines whether the given status is not successful.
 *
 * @param [in] status The status to test.
 * @return `0` if successful, non-zero otherwise.
 */
extern int edl_status_is_failure(edl_status status);
extern const char * edl_status_name(edl_status status);

#endif /* EDL_STATUS_HEADER */
