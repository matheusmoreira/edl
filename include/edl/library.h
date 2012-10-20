#ifndef EDL_LIBRARY_HEADER
#define EDL_LIBRARY_HEADER

#include <edl/function.h>
#include <edl/object.h>
#include <edl/status.h>

typedef struct edl_library edl_library;

extern edl_library * edl_library_create();
extern edl_status edl_library_destroy(edl_library * library);

extern edl_status edl_library_open(edl_library * library,
                                    const char * name);
extern edl_status edl_library_close(edl_library * library);
extern edl_status edl_library_current(edl_library * library);

extern edl_object edl_library_get_object(edl_library * library,
                                          const char * name);

extern edl_function edl_library_get_function(edl_library * library,
                                              const char * name);

extern const char * edl_library_last_error(edl_library * library);

#endif /* EDL_LIBRARY_HEADER */
