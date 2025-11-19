#include <Describer.hpp>
#include <FrameDesc.hpp>
#include <DrawItemDesc.hpp>

namespace Perspective::View {

render::FrameDesc Describer::describe(scene::Scene scene, scene::AssetStore assets) const
{
    return render::FrameDesc{};
}

render::DrawItemDesc Describer::describe(scene::Transform transform, scene::Renderable renderable, scene::AssetStore assets) const
{
    render::DrawItemDesc drawItemDesc{
        .modelMatrix = transform.getTransformMatrix(),
        .geometryId = renderable.getGeometryId(),
        .technicId = renderable.getTechnicId(),
    };
    return drawItemDesc;
}

} // namespace Perspective::View
