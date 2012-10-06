#ifndef EDL_LIBRARY_HEADER
#define EDL_LIBRARY_HEADER

#include <edl/status.h>

typedef struct edl_library edl_library_t;

extern edl_library_t * edl_library_create();
extern edl_status_t edl_library_destroy(edl_library_t * library);

extern edl_status_t edl_library_open(edl_library_t * library,
                                      const char * name);
extern edl_status_t edl_library_close(edl_library_t * library);
extern edl_status_t edl_library_current(edl_library_t * library);

extern void * edl_library_resolve_symbol(edl_library_t * library,
                                          const char * symbol);

extern const char * edl_library_last_error(edl_library_t * library);

#endif /* EDL_LIBRARY_HEADER */
