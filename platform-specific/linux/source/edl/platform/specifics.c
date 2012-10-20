#include <edl/platform/specifics.h>

#include <edl/function.h>
#include <edl/object.h>
#include <edl/status.h>

#include <dlfcn.h>

extern void * edl_native_library_open(const char * path) {
    return dlopen(path, RTLD_LAZY);
}

edl_object edl_native_library_get_object(void * native_handle,
                                         const char * name) {
    return (edl_object) dlsym(native_handle, name);
}

edl_function edl_native_library_get_function(void * native_handle,
                                             const char * name) {
    return (edl_function) edl_native_library_get_object(native_handle, name);
}

extern edl_status edl_native_library_close(void * native_handle) {
    return dlclose(native_handle) == 0 ? EDL_CLOSED_SUCCESSFULLY : EDL_FAILURE;
}

extern const char * edl_native_library_last_error() {
    return dlerror();
}
