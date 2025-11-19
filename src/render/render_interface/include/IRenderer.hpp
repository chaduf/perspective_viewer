
#pragma once

#include <Scene.hpp>

namespace Perspective::render {

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        virtual void initialize() = 0;
        virtual void render(Scene::Scene const& scene) const = 0;
        virtual void cleanup() = 0;

        virtual void draw (Scene::Node const& node) const = 0;

        // virtual void loadRenderable(Scene::Renderable const& renderable) = 0;
    };

} // namespace Perspective::render