#ifndef EDL_PLATFORM_SPECIFICS_HEADER
#define EDL_PLATFORM_SPECIFICS_HEADER

#include <edl/function.h>
#include <edl/object.h>
#include <edl/status.h>

/**
 * Obtains a platform-specific library handle using the given absolute or
 * relative path.
 *
 * @param [in] path The absolute or relative path to the library.
 * @return A pointer to the library handle, or `NULL` if it could not be
 *         obtained.
 */
extern void * edl_platform_specifics_library_open(const char * path);

extern edl_status edl_platform_specifics_library_close(void * native_handle);

extern edl_object edl_platform_specifics_get_object(void * native_handle,
                                                     const char * name);

extern edl_function edl_platform_specifics_library_get_function(void * native_handle,
                                                                 const char * name);

extern const char * edl_native_library_last_error();

#endif /* EDL_PLATFORM_SPECIFICS_HEADER */
