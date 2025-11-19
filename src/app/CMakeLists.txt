# look for SDL library
find_package(SDL3 REQUIRED)

# look for GLM library
find_package(glm REQUIRED)

if (NOT TARGET render)
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/render ${CMAKE_CURRENT_BINARY_DIR}/render)
endif()

if (NOT TARGET scene)
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/scene ${CMAKE_CURRENT_BINARY_DIR}/scene)
endif()

add_library(app STATIC
    implements/App.cpp
)

target_include_directories(app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(app PRIVATE
    render
    scene
    SDL3::SDL3
    glm::glm
)
