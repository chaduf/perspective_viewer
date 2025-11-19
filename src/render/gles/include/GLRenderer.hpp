#pragma once

#include <GLES3/gl3.h>

#include <IRenderer.hpp>
#include <Scene.hpp>
// #include <Mesh.hpp>

namespace Perspective::render::GLES {
    class GLRenderer : public IRenderer {
    public:
        GLRenderer();
        ~GLRenderer();

        GLRenderer(const GLRenderer&) = delete;
        GLRenderer& operator=(const GLRenderer&) = delete;
        GLRenderer(GLRenderer&&) noexcept = default;
        GLRenderer& operator=(GLRenderer&&) noexcept = default;

        void initialize() override;
        void render(Scene::Scene const& scene) const override;
        void draw(Scene::Node const& node) const override;
        void cleanup() override;

        void loadMesh();
        void drawMesh() const;

    private:
        std::unordered_map<std::string, IRenderer*> rendererMap_;
    };
} // namespace Perspective::render::GLES