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

/**
 * Destroys the platform-specific library handle.
 *
 * @param [in] native_handle The library handle to be closed.
 * @return
 *   - EDL_LIBRARY_CLOSED_SUCCESSFULLY
 *     - if the given library handle was closed successfully.
 *   - Any other status
 *     - if the given library handle was not closed successfully.
 */
extern edl_status edl_platform_specifics_library_close(void * native_handle);

/**
 * Obtains the address of the object referred to by the given `name`.
 *
 * @param [in] native_handle The handle to the library that contains the object.
 * @param [in] name The symbol which identifies the object.
 * @return A pointer to the object, or `NULL` if it could not be found.
 */
extern edl_object edl_platform_specifics_library_get_object(void * native_handle,
                                                             const char * name);

/**
 * Obtains the address of the function referred to by the given `name`.
 *
 * @param [in] native_handle The handle to the library that contains the
 *                           function.
 * @param [in] name The symbol which identifies the function.
 * @return A pointer to the function, or `NULL` if it could not be found.
 */
extern edl_function edl_platform_specifics_library_get_function(void * native_handle,
                                                                 const char * name);

/**
 * Obtains a description of the last error that occurred.
 *
 * @return A `NULL`-terminated string describing the last error that occurred,
 *         or `NULL` if no error has occurred.
 */
extern const char * edl_platform_specifics_library_last_error(void);

#endif /* EDL_PLATFORM_SPECIFICS_HEADER */
