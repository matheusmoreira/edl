#ifndef EDL_LIBRARY_HEADER
#define EDL_LIBRARY_HEADER

typedef struct edl_library edl_library_t;

extern edl_library_t * edl_library_new();
extern void edl_library_destroy(edl_library_t * library);

extern edl_library_t * edl_open_library(const char * name);
extern edl_library_t * edl_main_library();
extern int edl_close_library(edl_library_t * library);

extern void * edl_resolve_symbol(edl_library_t * library, const char * symbol);

extern const char * edl_last_error();

#endif /* EDL_LIBRARY_HEADER */
