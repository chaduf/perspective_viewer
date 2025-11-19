#include <Transform.hpp>
// #include <GLShaderProgram.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <iostream>

namespace Perspective::scene {
    Transform::Transform() : 
            position(0.0f, 0.0f, 0.0f), 
            rotation(0.0f, 0.0f, 0.0f, 1.0f), 
            scale(1.0f, 1.0f, 1.0f), 
            transformMatrixCache(1.0f), 
            isDirty(false), 
            isMatrixPure(false) {}

    Transform::Transform(const glm::mat4& matrix) {
        transformMatrixCache = matrix;
        isDirty = true;
        isMatrixPure = true;
    }

    glm::vec3 Transform::getPosition() {
        if (isMatrixPure) _decomposeTransformMatrix();
        return position;
    }

    glm::quat Transform::getRotationQuaternion() {
        if (isMatrixPure) _decomposeTransformMatrix();
        return rotation;
    }

    glm::vec3 Transform::getScale() {
        if (isMatrixPure) _decomposeTransformMatrix();
        return scale;
    }

    glm::mat4 Transform::getTransformMatrix() const {
        if (isMatrixPure) {
            return transformMatrixCache;
        }

        if (isDirty) {
            transformMatrixCache = glm::translate(glm::mat4(1.0f), position) *
                            glm::mat4_cast(rotation) *
                            glm::scale(glm::mat4(1.0f), scale);
            isDirty = false;
        }

        return transformMatrixCache;
    }

    // void Transform::apply(const GLShaderProgram& shaderProgram, const std::string& uniformName) const {
    //     glm::mat4 modelMatrix = getTransformMatrix();
    //     shaderProgram.setUniform(uniformName, modelMatrix);
    // }

    void Transform::_decomposeTransformMatrix() {
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(transformMatrixCache, scale, rotation, position, skew, perspective);
        isMatrixPure = false;
    }

    Transform Transform::operator*(const Transform& other) const {
        return Transform(this->getTransformMatrix() * other.getTransformMatrix());
    }

    Transform Transform::operator-(const Transform& other) const {
        return Transform(this->getTransformMatrix() - other.getTransformMatrix());
    }

    Transform Transform::operator+(const Transform& other) const {
        return Transform(this->getTransformMatrix() + other.getTransformMatrix());
    }
} // namespace Perspective::scene