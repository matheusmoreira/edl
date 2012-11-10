/**
 * @file
 *
 * Defines the `edl_api` structure and declares related functions.
 */

#ifndef EDL_API_HEADER
#define EDL_API_HEADER

#include <edl/api/function.h>
#include <edl/api/object.h>
#include <edl/library.h>
#include <edl/status.h>

/**
 * @brief Set of API objects and functions.
 *
 * Application Programming Interfaces consist of a set of exposed functions and
 * data, which are individually represented by `edl_api_function` and
 * `edl_api_object`, respectively.
 *
 * This structure may be passed to the `edl_api_initialize` function which,
 * given an open `edl_library`, will automatically link the library's functions
 * to the referenced function pointers.
 *
 *     edl_status status = EDL_FAILURE;
 *     void (*function)(int);
 *     int * integer;
 *
 *     edl_api api = {
 *
 *         .objects = (edl_api_object[]) {
 *             { "exposed_integer", (edl_object *) &integer }, { 0 }
 *         },
 *
 *         .functions = (edl_api_function[]) {
 *             { "exposed_function", (edl_function *) &function }, { 0 }
 *         }
 *
 *     };
 *
 *     status = edl_api_initialize(&api, library);
 *     if (edl_status_is_successful(status)) {
 *         // integer and function now point to the library's exposed_integer
 *         // and exposed_function
 *
 *         function(*integer);
 *     }
 *
 * `objects` and `functions` point to null-terminated arrays; the last element
 * must be `NULL`, or be a valid `edl_api_object` or `edl_api_function`
 * structure with the `name` member set to `NULL`;
 */
typedef struct edl_api {
    edl_api_object * objects; /**< Null-terminated array of API objects. */
    edl_api_function * functions; /**< Null-terminated array of API functions. */
} edl_api;

/**
 * Binds the objects and functions referenced by `api` to their associated
 * objects and functions in the `library`.
 *
 * If the given `api` is `NULL`, then this function was not given an API to
 * initialize and thus does nothing.
 *
 * @param [in] api The API to initialize. May be NULL.
 * @param [in] library The library that contains the objects and functions. Must
 *                     be initialized and open.
 * @return
 *   - `EDL_NULL_POINTER_ERROR`
 *     - if either the given API or the given library is NULL.
 *   - `EDL_API_LIBRARY_CLOSED_ERROR`
 *     - if the given library is not open.
 *   - `EDL_API_OBJECT_INITIALIZATION_ERROR`
 *     - if an object was not successfully initialized.
 *   - `EDL_API_FUNCTION_INITIALIZATION_ERROR`
 *     - if a function was not successfully initialized.
 *   - `EDL_API_INITIALIZED_SUCCESSFULLY`
 *     - if the entire API was successfully initialized.
 */
extern edl_status edl_api_initialize(edl_api * api, edl_library * library);

#endif /* EDL_API_HEADER */
