#include <stddef.h>

#include <edl/api.h>

#include <edl/api/object.h>
#include <edl/api/function.h>
#include <edl/function.h>
#include <edl/library.h>
#include <edl/object.h>
#include <edl/status.h>

/* edl_api interface implementation */

edl_status edl_api_initialize(edl_api * api, edl_library * library) {
    edl_api_object * api_object = NULL;
    edl_api_function * api_function = NULL;

    if (api == NULL) { return EDL_NOTHING_TO_DO; }
    if (library == NULL) { return EDL_API_LIBRARY_NOT_GIVEN_ERROR; }
    if (edl_library_is_closed(library)) { return EDL_API_LIBRARY_CLOSED_ERROR; }

    for (api_object = api->objects; api_object != NULL && api_object->name != NULL; ++api_object) {
        edl_object * object = api_object->object;

        if (object != NULL) {
            *object = edl_library_get_object(library, api_object->name);

            if (*object == NULL) { return EDL_API_OBJECT_INITIALIZATION_ERROR; }
        }
    }

    for (api_function = api->functions; api_function != NULL && api_function->name != NULL; ++api_function) {
        edl_function * function = api_function->function;

        if (function != NULL) {
            *function = edl_library_get_function(library, api_function->name);
        }

        if (*function == NULL) { return EDL_API_FUNCTION_INITIALIZATION_ERROR; }
    }

    return EDL_API_INITIALIZED_SUCCESSFULLY;
}
