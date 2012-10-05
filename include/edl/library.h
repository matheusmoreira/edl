#ifndef EDL_LIBRARY_HEADER
#define EDL_LIBRARY_HEADER

#include <edl/status.h>

typedef struct edl_library edl_library_t;

extern edl_library_t * edl_library_new();
extern void edl_library_destroy(edl_library_t * library);

extern edl_library_t * edl_library_open(const char * name);
extern edl_status_t edl_library_close(edl_library_t * library);
extern edl_library_t * edl_library_current();

extern void * edl_library_resolve_symbol(edl_library_t * library,
                                          const char * symbol);

extern const char * edl_library_last_error();

#endif /* EDL_LIBRARY_HEADER */
