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

    EDL_LIBRARY_CREATED_SUCCESSFULLY,
    EDL_LIBRARY_DESTROYED_SUCCESSFULLY,
    EDL_LIBRARY_OPENED_SUCCESSFULLY,
    EDL_LIBRARY_CLOSED_SUCCESSFULLY,
    EDL_LIBRARY_ALREADY_CLOSED,
    EDL_LIBRARY_OBJECT_FOUND,
    EDL_LIBRARY_FUNCTION_FOUND,

    EDL_FAILURE,

    EDL_NULL_POINTER_ERROR,
    EDL_MEMORY_ALLOCATION_ERROR,

    EDL_API_LIBRARY_CLOSED_ERROR,
    EDL_API_OBJECT_INITIALIZATION_ERROR,
    EDL_API_FUNCTION_INITIALIZATION_ERROR,

    EDL_LIBRARY_CLOSED_ERROR,
    EDL_LIBRARY_ALREADY_OPENED_ERROR,
    EDL_LIBRARY_SHARED_OBJECT_NOT_FOUND_ERROR,
    EDL_LIBRARY_OBJECT_NOT_FOUND_ERROR,
    EDL_LIBRARY_FUNCTION_NOT_FOUND_ERROR
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

/**
 * Returns the string representation of the given status.
 *
 * @note The strings returned by this function are not dynamically allocated and
 *       must not be freed.
 *
 * @param [in] status The status whose string representation is desired.
 * @return The string representation of the status.
 */
extern const char * edl_status_name(edl_status status);

#endif /* EDL_STATUS_HEADER */
