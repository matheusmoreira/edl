#ifndef EDL_LIBRARY_HEADER
#define EDL_LIBRARY_HEADER

#include <edl/function.h>
#include <edl/object.h>
#include <edl/status.h>

/**
 * @brief Loadable dynamic library.
 *
 * `edl_library` is an opaque structure which represents a dynamic library.
 * Through the library handle, its functions and variables can be made available
 * to the program at runtime without linking against the library at compile
 * time.
 *
 *     void (*function)();
 *     edl_status status = EDL_FAILURE;
 *     edl_library library = NULL;
 *
 *     status = edl_library_create(&library);
 *     if (edl_status_is_successful(status)) {
 *         status = edl_library_open(library, "/path/to/library.so");
 *
 *         if (edl_status_is_successful(status)) {
 *             status = edl_library_get_function(library, "function", &function);
 *
 *             if (edl_status_is_successful(status)) { function(); }
 *         }
 *     }
 *
 *     status = edl_library_destroy(library);
 */
typedef struct edl_library edl_library;

/**
 * Allocates and initializes memory for a new library and makes the given
 * `library` reference point to it.
 *
 * @param [out] library_reference Pointer to the library pointer which will be
 *                                initialized with the address of the
 *                                newly-created library.
 * @return
 *   - EDL_NULL_POINTER_ERROR
 *     - if the given library reference is `NULL`.
 *   - EDL_MEMORY_ALLOCATION_ERROR
 *     - if memory for the library could not be allocated.
 *   - EDL_LIBRARY_CREATED_SUCCESSFULLY
 *     - if the library was successfully created.
 * @see edl_library_destroy
 */
extern edl_status edl_library_create(edl_library ** library_reference);

/**
 * Frees the memory allocated for the library pointed to by the given reference.
 * If the library is still open, it will be closed.
 *
 * @note After the library was successfully destroyed, the value pointed to by
 *       `library_reference` will be set to `NULL`.
 *
 * @param [in] library_reference Reference to the library pointer that will be
 *                               freed.
 * @return
 *   - EDL_NULL_POINTER_ERROR
 *     - if the given library reference is `NULL`.
 *   - EDL_NOTHING_TO_DO
 *     - if the library pointed to by the given library reference is `NULL`.
 *   - The status returned by `edl_library_close()`
 *     - if the library was still open and could not be closed successfully.
 *   - EDL_LIBRARY_DESTROYED_SUCCESSFULLY
 *     - if the library was successfully destroyed.
 * @see edl_library_close
 */
extern edl_status edl_library_destroy(edl_library ** library_reference);

/**
 * Searches for the dynamic library given by `name`, obtains a handle to the
 * shared object and associates it with the given `library`.
 *
 * If the given `name` is `NULL`, the current process will be opened as a
 * library.
 *
 * @param [in] library The library to be opened.
 * @param [in] name The relative or absolute path to the library's shared
 *                  object. May be `NULL`.
 * @return
 *   - EDL_NULL_POINTER_ERROR
 *     - if the given library is `NULL`.
 *   - EDL_LIBRARY_ALREADY_OPENED_ERROR
 *     - if the given library has already been opened.
 *   - EDL_LIBRARY_SHARED_OBJECT_NOT_FOUND_ERROR
 *     - if a handle to the library's shared object could not be obtained.
 *   - EDL_LIBRARY_OPENED_SUCCESSFULLY
 *     - if the library was successfully opened.
 */
extern edl_status edl_library_open(edl_library * library,
                                    const char * name);

/**
 * Closes the handle to the `library`'s shared object.
 *
 * @param [in] library The library to be closed.
 * @return
 *   - EDL_NULL_POINTER_ERROR
 *     - if the given library is `NULL`.
 *   - EDL_LIBRARY_ALREADY_CLOSED
 *     - if the library is already closed.
 *   -  The status returned by `edl_native_library_close()`
 *     - if the library could not be closed successfully.
 *   - EDL_LIBRARY_CLOSED_SUCCESSFULLY
 *     - if the library was successfully closed.
 */
extern edl_status edl_library_close(edl_library * library);

/**
 * Opens the current process as a dynamic library and associates the handle with
 * the given `library`.
 *
 * This is the same as calling `edl_library_open(library, NULL)`.
 *
 * @param [in] library The library to be opened.
 * @return
 *   - EDL_NULL_POINTER_ERROR
 *     - if the given library is `NULL`.
 *   - EDL_LIBRARY_ALREADY_OPENED_ERROR
 *     - if the given library has already been opened.
 *   - EDL_LIBRARY_SHARED_OBJECT_NOT_FOUND_ERROR
 *     - if the current process could not be opened as a library.
 *   - EDL_LIBRARY_OPENED_SUCCESSFULLY
 *     - if the current process was successfully opened as a library.
 */
extern edl_status edl_library_current(edl_library * library);

/**
 * Returns a pointer to data exported by the `library`.
 *
 * @param [in] library The library that contains the data.
 * @param [in] name The symbol that identifies the exported data.
 * @param [out] object Pointer to the object pointer which will be initialized
 *                     with the address of the external data.
 * @return
 *   - EDL_NULL_POINTER_ERROR
 *     - if either the library, name or object pointer is `NULL`.
 *   - EDL_LIBRARY_CLOSED_ERROR
 *     - if given a closed library.
 *   - EDL_LIBRARY_OBJECT_NOT_FOUND_ERROR
 *     - if the requested object could not be found in the given library.
 *   - EDL_LIBRARY_FUNCTION_FOUND
 *     - if the requested object was found and the given object pointer set.
 */
extern edl_status edl_library_get_object(edl_library * library,
                                          const char * name,
                                          edl_object * object);

/**
 * Returns a pointer to a function exported by the `library`.
 *
 * @param [in] library The library that contains the function.
 * @param [in] name The symbol that identifies the exported function.
 * @param [out] function Pointer to the function pointer which will be
 *                       initialized with the address of the external function.
 * @return
 *   - EDL_NULL_POINTER_ERROR
 *     - if either the library, name or function pointer is `NULL`.
 *   - EDL_LIBRARY_CLOSED_ERROR
 *     - if given a closed library.
 *   - EDL_LIBRARY_FUNCTION_NOT_FOUND_ERROR
 *     - if the requested function could not be found in the given library.
 *   - EDL_LIBRARY_FUNCTION_FOUND
 *     - if the requested function was found and the given function pointer set.
 */
extern edl_status edl_library_get_function(edl_library * library,
                                            const char * name,
                                            edl_function * function);

/**
 * Determines whether the given `library` is open.
 *
 * @param [in] library The library to test.
 * @return `0` if the library is closed or `NULL`, non-zero otherwise.
 */
extern int edl_library_is_open(edl_library * library);

/**
 * Determines whether the given `library` is closed.
 *
 * @param [in] library The library to test.
 * @return Non-zero if the library is closed or `NULL`, `0` otherwise.
 */
extern int edl_library_is_closed(edl_library * library);

/**
 * Returns the last error message associated with the given `library`.
 *
 * @note The strings returned by this function are not dynamically allocated and
 *       must not be freed.
 *
 * @param [in] library The library.
 * @return Null-terminated strings containing a human-readable description of
 *         the last error that occurred with the library, or NULL if the given
 *         library is `NULL` or if no error occurred.
 */
extern const char * edl_library_last_error(edl_library * library);

#endif /* EDL_LIBRARY_HEADER */
