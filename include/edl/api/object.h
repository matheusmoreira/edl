/**
 * @file
 *
 * Defines the `edl_api_object` structure.
 */

#ifndef EDL_API_OBJECT_HEADER
#define EDL_API_OBJECT_HEADER

#include <edl/object.h>

/**
 * @brief Represents a data object which is part of an external API.
 *
 * `edl_api_object` associates the name that identifies external data with the
 * local object pointer that will be made to point to it.
 */
typedef struct edl_api_object {
    const char * name; /**< Symbol which identifies the object. */
    edl_object * object; /**< `edl_object` which will point to the external data. */
} edl_api_object;

#endif /* EDL_API_OBJECT_HEADER */
