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

get_filename_component(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../.. REALPATH)

project(scene_unit_tests LANGUAGES CXX)

find_package(glm REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(scene_unit_tests ${TEST_SOURCES})

if (NOT TARGET scene)
  add_subdirectory(${PROJECT_ROOT_DIR}/src/scene ${CMAKE_BINARY_DIR}/scene)
endif()

target_include_directories(scene_unit_tests PRIVATE
    ${PROJECT_ROOT_DIR}/src/scene/include
)

target_link_libraries(scene_unit_tests PRIVATE
    scene
    gtest_main
    glm::glm
)

include(GoogleTest)
gtest_discover_tests(scene_unit_tests)
