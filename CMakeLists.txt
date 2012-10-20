cmake_minimum_required(VERSION 2.8)

# Set up EDL project
project(edl C)
set(BUILD_SHARED_LIBS ON)
set(EDL_LIBRARY ${PROJECT_NAME})

# Set up base directories
set(EDL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(EDL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(EDL_PLATFORM_SPECIFIC_DIR ${PROJECT_SOURCE_DIR}/platform-specific)

message("Include directory: ${EDL_INCLUDE_DIR}")
message("Source directory: ${EDL_SOURCE_DIR}")
message("Platform-specific directory: ${EDL_PLATFORM_SPECIFIC_DIR}")

# Make main library files accessible
include_directories(${EDL_INCLUDE_DIR})
file(GLOB_RECURSE EDL_SOURCE_FILES ${EDL_SOURCE_DIR}/*.c)

# Detect underlying system
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(EDL_PLATFORM linux)
else()
  message("WARNING: platform not supported")
endif()

message("Platform: ${EDL_PLATFORM}")

# Load platform-specific build instructions
include(${EDL_PLATFORM_SPECIFIC_DIR}/${EDL_PLATFORM}/build-instructions.cmake)

message("Platform-specific libraries: ${EDL_PLATFORM_SPECIFIC_LIBRARIES}")

# Find platform-specific libraries
foreach(LIBRARY ${EDL_PLATFORM_SPECIFIC_LIBRARIES})
  find_library(${LIBRARY} REQUIRED)
endforeach()

# Set up platform-specific directories
set(EDL_PLATFORM_SPECIFIC_INCLUDE_DIR
    ${EDL_PLATFORM_SPECIFIC_DIR}/${EDL_PLATFORM}/include)
set(EDL_PLATFORM_SPECIFIC_SOURCE_DIR
    ${EDL_PLATFORM_SPECIFIC_DIR}/${EDL_PLATFORM}/source)

message("Platform-specific include directory: ${EDL_PLATFORM_SPECIFIC_INCLUDE_DIR}")
message("Platform-specific source directory: ${EDL_PLATFORM_SPECIFIC_SOURCE_DIR}")

# Make platform-specific files accessible
include_directories(${EDL_PLATFORM_SPECIFIC_INCLUDE_DIR})
file(GLOB_RECURSE EDL_PLATFORM_SPECIFIC_SOURCE_FILES
     ${EDL_PLATFORM_SPECIFIC_SOURCE_DIR}/*.c)

# Configure EDL library
add_library(${EDL_LIBRARY}
            ${EDL_SOURCE_FILES} ${EDL_PLATFORM_SPECIFIC_SOURCE_FILES})

# Link against platform-specific libraries
add_dependencies(${EDL_LIBRARY} ${EDL_PLATFORM_SPECIFIC_LIBRARIES})
target_link_libraries(${EDL_LIBRARY}
                      ${EDL_PLATFORM_SPECIFIC_LIBRARIES})

# Build examples
add_subdirectory(examples)
