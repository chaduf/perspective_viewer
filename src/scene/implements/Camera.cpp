#include <Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : viewTransform(), projectionTransform() {}

void Camera::lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
    glm::mat4 viewMatrix = glm::lookAt(eye, target, up);
    viewTransform = Transform(viewMatrix);
}