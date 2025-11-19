#pragma once

#include <Scene.hpp>
#include <Renderable.hpp>
#include <AssetStore.hpp>
#include <FrameDesc.hpp>
#include <DrawItemDesc.hpp>

namespace Perspective::View {

class Describer {
public:
    Describer() = default;
    Describer(const Describer&) = default;
    Describer& operator=(const Describer&) = default;
    Describer(Describer&&) noexcept = default;
    Describer& operator=(Describer&&) noexcept = default;
    virtual ~Describer() = default;

    render::FrameDesc describe(scene::Scene scene, scene::AssetStore assets) const;
    render::DrawItemDesc describe(scene::Transform transform, 
        scene::Renderable node, scene::AssetStore assets) const;
};

} // namespace Perspective::View
