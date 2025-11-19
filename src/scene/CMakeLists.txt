cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable debug symbols
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 ")
endif()

# Set binary output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

get_filename_component(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../.. REALPATH)

if (NOT TARGET core)
    add_subdirectory(${PROJECT_ROOT_DIR}/src/core ${CMAKE_CURRENT_BINARY_DIR}/core)
endif()
    
add_library(scene STATIC
    implements/Node.cpp
    implements/Transform.cpp
    implements/Scene.cpp
    implements/Renderable.cpp
    implements/Geometry.cpp
    implements/Stage.cpp
    implements/Technic.cpp
    implements/AssetStore.cpp
    implements/SceneController.cpp
)

target_include_directories(scene PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# look for GLM library
find_package(glm REQUIRED)

# Dépendances spécifiques au module
target_link_libraries(scene PUBLIC
    core
    glm::glm
)
