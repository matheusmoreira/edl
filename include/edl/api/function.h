/**
 * @file
 *
 * Defines the `edl_api_function` structure.
 */

#ifndef EDL_API_FUNCTION_HEADER
#define EDL_API_FUNCTION_HEADER

#include <edl/function.h>

typedef struct edl_api_function {
    const char * name;
    edl_function * function;
} edl_api_function;

#endif /* EDL_API_FUNCTION_HEADER */
