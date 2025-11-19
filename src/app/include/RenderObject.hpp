#pragma once

#include <ShaderProgram.hpp>
#include <Mesh.hpp>
#include <Material.hpp>
#include <Transform.hpp>
#include <Camera.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <optional>

class RenderObjectBuilder;

class RenderObject {
    friend class RenderObjectBuilder;
private:
    // Constructors
    RenderObject() : 
        mesh(nullptr), 
        shaderProgram(nullptr), 
        material(nullptr), 
        transform(nullptr) {}

public:
    // Copy constructor and assignment
    RenderObject(const RenderObject& other) = default;
    RenderObject& operator=(const RenderObject& other) = default;
    
    // Move constructor and assignment
    RenderObject(RenderObject&& other) = default;
    RenderObject& operator=(RenderObject&& other) = default;

    ~RenderObject() {}
    
    // Getters
    std::vector<std::shared_ptr<RenderObject>> getChildren() const { return children; }
    std::shared_ptr<GLShaderProgram> getShaderProgram() const { return shaderProgram; }
    std::shared_ptr<Geometry> getMesh() const { return mesh; }
    std::shared_ptr<Material> getMaterial() const { return material; }
    std::shared_ptr<Transform> getTransform() const { return transform; }

    // Public methods
    void initialize();
    void draw(const Transform& reference = Transform(), const Camera& camera = Camera()) const;
    void attachChild(std::shared_ptr<RenderObject> child) { children.push_back(child); }

private:
    // Attributes
    std::shared_ptr<GLShaderProgram> shaderProgram;
    std::vector<std::shared_ptr<RenderObject>> children;
    std::shared_ptr<Geometry> mesh;
    std::shared_ptr<Material> material;
    std::shared_ptr<Transform> transform;

    // Setters
};

class RenderObjectBuilder {
public:
    RenderObjectBuilder() : 
        mesh(nullptr), 
        shaderProgram(nullptr), 
        material(nullptr), 
        transform(nullptr) {}

    RenderObjectBuilder& setShaderProgram(std::shared_ptr<GLShaderProgram> shaderProgram) {
        this->shaderProgram = shaderProgram;
        return *this;
    }

    RenderObjectBuilder& setMesh(std::shared_ptr<Geometry> mesh) {
        this->mesh = mesh;
        return *this;
    }

    RenderObjectBuilder& setMaterial(std::shared_ptr<Material> material) {
        this->material = material;
        return *this;
    }

    RenderObjectBuilder& setTransform(std::shared_ptr<Transform> transform) {
        this->transform = transform;
        return *this;
    }

    std::optional<RenderObject> build() const;

private:
    std::shared_ptr<Geometry> mesh;
    std::shared_ptr<GLShaderProgram> shaderProgram;
    std::shared_ptr<Material> material;
    std::shared_ptr<Transform> transform;
};
