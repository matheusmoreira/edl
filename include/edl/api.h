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

typedef struct edl_api {
    edl_api_object * objects;
    edl_api_function * functions;
} edl_api;

extern edl_status edl_api_initialize(edl_api * api, edl_library * library);

#endif /* EDL_API_HEADER */
