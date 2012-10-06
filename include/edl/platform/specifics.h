#ifndef EDL_PLATFORM_SPECIFICS_HEADER
#define EDL_PLATFORM_SPECIFICS_HEADER

#include <edl/function.h>
#include <edl/object.h>
#include <edl/status.h>

extern void * edl_native_library_open(const char * path);
extern edl_status_t edl_native_library_close(void * native_handle);

extern edl_object_t edl_native_library_get_object(void * native_handle,
                                                   const char * name);

extern edl_function_t edl_native_library_get_function(void * native_handle,
                                                       const char * name);

extern const char * edl_native_library_last_error();

#endif /* EDL_PLATFORM_SPECIFICS_HEADER */
