#ifndef EDL_HEADER
#define EDL_HEADER

typedef struct edl_library {
    const char * name;
    void * native_handle;
} edl_library_t;

extern edl_library_t * edl_open_library(const char * name);
extern edl_library_t * edl_main_library();
extern int edl_close_library(edl_library_t * library);

extern void * edl_resolve_symbol(edl_library_t * library, const char * symbol);

extern const char * edl_last_error();

#endif /* EDL_HEADER */
