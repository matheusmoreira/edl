#ifndef EDL_API_OBJECT_HEADER
#define EDL_API_OBJECT_HEADER

#include <edl/object.h>

typedef struct edl_api_object {
    const char * name;
    edl_object * object;
} edl_api_object;

#endif /* EDL_API_OBJECT_HEADER */
