cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_filename_component(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../.. REALPATH)

project(scene_unit_tests LANGUAGES CXX)

find_package(glm REQUIRED)

## Add dependencies for this module
if (NOT TARGET scene)
  add_subdirectory(${PROJECT_ROOT_DIR}/src/scene ${CMAKE_CURRENT_BINARY_DIR}/scene)
endif()

if (NOT TARGET render_interface)
  add_subdirectory(${PROJECT_ROOT_DIR}/src/render/render_interface ${CMAKE_CURRENT_BINARY_DIR}/render_interface)
endif()

add_library(view STATIC
    implements/Describer.cpp
)

target_include_directories(view PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

target_link_libraries(view PRIVATE
    scene
    glm::glm
)
