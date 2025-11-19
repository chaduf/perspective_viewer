#pragma once

#include <vector>
#include <iostream>

#include <glm/glm.hpp>

namespace Perspective::render {

    struct CameraDesc {
        glm::mat4 viewMatrix{1.0f};
        glm::mat4 projectionMatrix{1.0f};
        glm::vec3 position{0.0f, 0.0f, 0.0f};
        float nearPlane{0.1f};
        float farPlane{100.0f};
    };

} // namespace Perspective::render