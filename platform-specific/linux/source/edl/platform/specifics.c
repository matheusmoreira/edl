#include <edl/platform/specifics.h>

#include <dlfcn.h>

extern void * edl_native_open_library(const char * path) {
    return dlopen(path, RTLD_LAZY);
}

extern void * edl_native_resolve_symbol(void * native_handle, const char * symbol) {
    return dlsym(native_handle, symbol);
}

extern int edl_native_close_library(void * native_handle) {
    return dlclose(native_handle);
}

extern const char * edl_native_last_error() {
    return dlerror();
}
