#include <iostream>

#include <GLRenderer.hpp>

// A supprimerer plus tard
#include <Geometry.hpp>

namespace Perspective::render::GLES {
    GLRenderer::GLRenderer() {
        // Constructor implementation
    }

    GLRenderer::~GLRenderer() {
        // Destructor implementation
    }

    void GLRenderer::initialize() {
        glViewport(0, 0, 800, 600);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
    }

    void GLRenderer::render(Scene::Scene const& scene) const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Rendering code using scene and camera
    }

    void GLRenderer::draw(Scene::Node const& node) const {
        // Drawing code for a node
    }


    void GLRenderer::cleanup() {
        // Cleanup code
    }
} // namespace Perspective::render::GLES
