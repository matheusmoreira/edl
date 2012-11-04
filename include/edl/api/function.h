/**
 * @file
 *
 * Defines the `edl_api_function` structure.
 */

#ifndef EDL_API_FUNCTION_HEADER
#define EDL_API_FUNCTION_HEADER

#include <edl/function.h>

/**
 * @brief Represents a function that is part of an external API.
 *
 * `edl_api_function` associates the name associated with an exported function
 * with the local function pointer that will be made to point to it.
 */
typedef struct edl_api_function {
    const char * name; /**< Symbol which identifies the external function. */
    edl_function * function; /**< `edl_function` which will point to the external function. */
} edl_api_function;

#endif /* EDL_API_FUNCTION_HEADER */
