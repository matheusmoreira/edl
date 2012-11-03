add_executable(api api.c)
target_link_libraries(api ${EDL_LIBRARY})

add_subdirectory(library)
