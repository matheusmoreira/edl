/**
 * @file
 *
 * Defines the `edl_object` type.
 */

#ifndef EDL_OBJECT_HEADER
#define EDL_OBJECT_HEADER

/**
 * @brief Generic variable pointer.
 *
 * `edl_object` is an intermediary type which represents a generic data pointer.
 * It can point to variables of any type, but cannot be dereferenced directly;
 * it must be cast to the proper pointer type prior to use.
 */
typedef void * edl_object;

#endif /* EDL_OBJECT_HEADER */
