

# Recherche explicite de la bibliothèque GLESv2
find_library(GLESv2_LIBRARY NAMES GLESv2 PATHS /usr/lib/x86_64-linux-gnu REQUIRED)
message(STATUS "GLESv2_LIBRARY: ${GLESv2_LIBRARY}")

add_library(render STATIC
    implements/GLRenderer.cpp
    implements/GLShaderProgram.cpp
    implements/GLShader.cpp
)

target_include_directories(render PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(render PUBLIC render_interface
    core
    scene
    ${GLESv2_LIBRARY}
)
