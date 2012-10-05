#ifndef EDL_PLATFORM_SPECIFICS_HEADER
#define EDL_PLATFORM_SPECIFICS_HEADER

#include <edl/status.h>

extern void * edl_native_open_library(const char * path);
extern edl_status_t edl_native_close_library(void * native_handle);

extern void * edl_native_resolve_symbol(void * native_handle,
                                         const char * symbol);

extern const char * edl_native_last_error();

#endif /* EDL_PLATFORM_SPECIFICS_HEADER */
