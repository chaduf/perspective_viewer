#pragma once

#include <Transform.hpp>

class Camera {
public:
    Camera();
    ~Camera() = default;

    void lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);

private:
    Transform viewTransform;
    Transform projectionTransform;
};
