/**
 * @file edl/api.h
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
    edl_api_function * functions;
} edl_api;

extern edl_status edl_api_initialize(edl_api * api, edl_library * library);

#endif /* EDL_API_HEADER */
