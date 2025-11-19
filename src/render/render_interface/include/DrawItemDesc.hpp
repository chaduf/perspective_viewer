#pragma once

#include <glm/glm.hpp>

#include <string>
#include <optional>


namespace Perspective::render {

    struct DrawItemDesc {
        glm::mat4 modelMatrix{1.0f};

        std::optional<std::string> geometryId;
        std::optional<std::string> materialId;
        std::optional<std::string> technicId;
    };
} // namespace Perspective::render