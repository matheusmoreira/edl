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
 * @return Pointer to the library.
 * @see edl_library_destroy
 */
extern edl_library * edl_library_create();
extern edl_status edl_library_destroy(edl_library * library);

extern edl_status edl_library_open(edl_library * library,
                                    const char * name);
extern edl_status edl_library_close(edl_library * library);
extern edl_status edl_library_current(edl_library * library);

extern edl_object edl_library_get_object(edl_library * library,
                                          const char * name);

extern edl_function edl_library_get_function(edl_library * library,
                                              const char * name);

extern int edl_library_is_open(edl_library * library);
extern int edl_library_is_closed(edl_library * library);

extern const char * edl_library_last_error(edl_library * library);

#endif /* EDL_LIBRARY_HEADER */
