#include <stddef.h>

#include <edl/api.h>

#include <edl/api/function.h>
#include <edl/api/object.h>
#include <edl/library.h>
#include <edl/status.h>

/* edl_api interface implementation */

edl_status edl_api_initialize(edl_api * api, edl_library * library) {
    edl_api_object * api_object = NULL;
    edl_api_function * api_function = NULL;
    edl_status status = EDL_FAILURE;

    if (api == NULL) { return EDL_NOTHING_TO_DO; }
    if (library == NULL) { return EDL_API_LIBRARY_NOT_GIVEN_ERROR; }
    if (edl_library_is_closed(library)) { return EDL_API_LIBRARY_CLOSED_ERROR; }

    for (api_object = api->objects; api_object != NULL && api_object->name != NULL; ++api_object) {
        if (api_object->object != NULL) {
            status = edl_library_get_object(library, api_object->name, api_object->object);

            if (edl_status_is_failure(status)) { return EDL_API_OBJECT_INITIALIZATION_ERROR; }
        }
    }

    for (api_function = api->functions; api_function != NULL && api_function->name != NULL; ++api_function) {
        if (api_function->function != NULL) {
            status = edl_library_get_function(library, api_function->name, api_function->function);

            if (edl_status_is_failure(status)) { return EDL_API_FUNCTION_INITIALIZATION_ERROR; }
        }
    }

    return EDL_API_INITIALIZED_SUCCESSFULLY;
}
