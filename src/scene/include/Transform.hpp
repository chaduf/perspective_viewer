#pragma once

#include <mtools.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/quaternion.hpp>

#include <array>
#include <string>

namespace Perspective::scene {
    class Transform {
    public:
        Transform();
        ~Transform() = default;
        Transform(const glm::mat4& matrix);

        bool operator==(const Transform& other) const {
            const float eps = 1e-6f;
            if (!glm::all(glm::epsilonEqual(position, other.position, eps))) return false;
            if (!core::mtools::epsilonEqual(rotation, other.rotation, eps)) return false;
            if (!glm::all(glm::epsilonEqual(scale, other.scale, eps))) return false;
            glm::mat4 m1 = getTransformMatrix();
            glm::mat4 m2 = other.getTransformMatrix();
            if (!core::mtools::epsilonEqual(m1, m2, eps)) return false;
            if (isDirty != other.isDirty) return false;
            if (isMatrixPure != other.isMatrixPure) return false;
            return true;
        }

        bool operator!=(const Transform& other) const {
            return !(*this == other);
        }

        // Setters
        void setPosition(glm::vec3 position) { this->position = position; isDirty = true; }
        void setRotation(glm::quat rotation) { this->rotation = rotation; isDirty = true; }
        void setScale(glm::vec3 scale) { this->scale = scale; isDirty = true; }

        // Getters (recomputed if pure matrix)
        glm::vec3 getPosition();
        glm::quat getRotationQuaternion();
        glm::vec3 getScale();

        // Get the transformation matrix (recomputed if dirty)
        glm::mat4 getTransformMatrix() const;

        // Matrix operations (return pure matrices)
        Transform operator*(const Transform& other) const;
        Transform operator-(const Transform& other) const;
        Transform operator+(const Transform& other) const;

        // void apply(const GLShaderProgram& shaderProgram, const std::string& uniformName) const;

    private:
        glm::vec3 position = {0.0f, 0.0f, 0.0f};
        glm::quat rotation = {0.0f, 0.0f, 0.0f, 1.0f};
        glm::vec3 scale = {1.0f, 1.0f, 1.0f};

        mutable glm::mat4 transformMatrixCache = glm::mat4(1.0f);
        mutable bool isDirty = true; // true if transform has changed
        mutable bool isMatrixPure = false; // True if transform is defined by matrix only

        // Update the transform parameters by decomposing the transformation matrix turning
        // pure matrix transforms into clean matrix position/rotation/scale
        void _decomposeTransformMatrix();

    };
} // namespace Perspective::scene
