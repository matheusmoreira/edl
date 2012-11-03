/**
 * @file
 *
 * Defines the `edl_function` type.
 */

#ifndef EDL_FUNCTION_HEADER
#define EDL_FUNCTION_HEADER

/**
 * @brief Generic function pointer.
 *
 * `edl_function` is an intermediary type which represents a generic function
 * pointer. It should be cast to a function pointer type with the proper
 * signature prior to use.
 */
typedef void (*edl_function)();

#endif /* EDL_FUNCTION_HEADER */
