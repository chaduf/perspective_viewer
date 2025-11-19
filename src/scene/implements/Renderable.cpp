#include <Renderable.hpp>

#include <utility>

namespace Perspective::scene {

Renderable& Renderable::setGeometryId(std::string id) noexcept
{
    geometryId_ = std::optional<std::string>(std::move(id));
    return *this;
}

Renderable& Renderable::setTechnicId(std::string id) noexcept
{
    technicId_ = std::optional<std::string>(std::move(id));
    return *this;
}

Renderable& Renderable::initialize()
{
    // TODO: Initialize material, mesh, shaderProgram if needed
    return *this;
}

} // namespace Perspective::scene
