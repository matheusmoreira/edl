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
 *     edl_library library = edl_library_create();
 *
 *     if (library != NULL) {
 *         status = edl_library_open(library, "/path/to/library.so");
 *
 *         if (edl_status_is_successful(status)) {
 *             function = edl_library_get_function(library, "function");
 *
 *             if (function != NULL) { function(); }
 *         }
 *     }
 *
 *     status = edl_library_destroy(library);
 */
typedef struct edl_library edl_library;

/**
 * Allocates and initializes memory for a new library and returns a pointer to
 * it.
 *
 * @return Pointer to the newly-created library.
 * @see edl_library_destroy
 */
extern edl_library * edl_library_create();

/**
 * Frees the memory allocated for the library. If the library is still open, it
 * will be closed.
 *
 * @param [in] library The library to destroy. May be `NULL`.
 * @return
 *   - EDL_NOTHING_TO_DO
 *     - if there is no library to destroy.
 *   - The status returned by `edl_library_close()`
 *     - if the library was still open and could not be closed successfully.
 *   - EDL_LIBRARY_DESTROYED_SUCCESSFULLY
 *     - if the library was successfully destroyed.
 */
extern edl_status edl_library_destroy(edl_library * library);

/**
 * Searches for the dynamic library given by `name`, obtains a handle to the
 * shared object and associates it with the given `library`.
 *
 * If the given `name` is `NULL`, the current process will be opened as a
 * library.
 *
 * @param [in] library The library to be opened. May be `NULL`.
 * @param [in] name The relative or absolute path to the library's shared
 *                  object. May be `NULL`.
 * @return
 *   - EDL_NOTHING_TO_DO
 *     - if there is no library to open.
 *   - EDL_FAILURE
 *     - if a handle to the library's shared object could not be obtained.
 *   - EDL_SUCCESS
 *     - if the library was successfully opened.
 */
extern edl_status edl_library_open(edl_library * library,
                                    const char * name);

/**
 * Closes the handle to the library's shared object.
 *
 * @param [in] library The library to be closed. May be `NULL`.
 * @return
 *   - EDL_NOTHING_TO_DO
 *     - if there is no library to close.
 *   - EDL_LIBRARY_ALREADY_CLOSED
 *     - if the library is already closed.
 *   -  The status returned by `edl_native_library_close()`
 *     - if the library could not be closed successfully.
 *   - EDL_LIBRARY_CLOSED_SUCCESSFULLY
 *     - if the library was successfully closed.
 */
extern edl_status edl_library_close(edl_library * library);

/**
 * Opens the current process as a dynamic library.
 *
 * This is the same as calling `edl_library_open(library, NULL)`.
 *
 * @param [in] library The library to be opened. May be `NULL`.
 * @return
 *   - EDL_NOTHING_TO_DO
 *     - if there is no library to open.
 *   - EDL_FAILURE
 *     - if a handle to the library's shared object could not be obtained.
 *   - EDL_SUCCESS
 *     - if the library was successfully opened.
 */
extern edl_status edl_library_current(edl_library * library);

/**
 * Returns a pointer to data exported by the `library`.
 *
 * @param [in] library The library that contains the data. May be `NULL`.
 * @param [in] name The symbol that identifies the exported data.
 * @return Pointer to the data, or NULL if not given a library or if any error
 *         occurs.
 */
extern edl_object edl_library_get_object(edl_library * library,
                                          const char * name);

/**
 * Returns a pointer to a function exported by the `library`.
 *
 * @param [in] library The library that contains the function. May be `NULL`.
 * @param [in] name The symbol that identifies the exported function.
 * @return Pointer to the function, or NULL if not given a library or if any
 *         error occurs.
 */
extern edl_function edl_library_get_function(edl_library * library,
                                              const char * name);

/**
 * Determines whether the library is open.
 *
 * @param [in] library The library to test.
 * @return Non-zero if the library is open, `0` otherwise.
 */
extern int edl_library_is_open(edl_library * library);

/**
 * Determines whether the library is closed.
 *
 * @param [in] library The library to test.
 * @return Non-zero if the library is closed, `0` otherwise.
 */
extern int edl_library_is_closed(edl_library * library);

extern const char * edl_library_last_error(edl_library * library);

#endif /* EDL_LIBRARY_HEADER */
