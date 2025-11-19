cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_FIND_DEBUG_MODE 1)

# Export compile commands for VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable debug symbols
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 ")
endif()

project(perspective-viewer)

#include opengl_driver and world_editor 
add_subdirectory(src/app)

# Include unit tests subdirectory if present
add_subdirectory(tests/scene)

add_executable(perspective-viewer WIN32
    src/main.cpp
)

target_link_libraries(perspective-viewer PRIVATE
    app
    render
    scene
)
