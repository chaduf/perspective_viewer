#include <RenderObject.hpp>

#include <iostream>

// Render method
void RenderObject::draw(const Transform& reference, const Camera& camera) const {

    if (shaderProgram && mesh) {
        shaderProgram->use();

        if (transform) { 
            transform->apply(*shaderProgram, "model");
        }
        if (material) {
            material->apply(*shaderProgram);
        }
        camera.apply(*shaderProgram);

        mesh->draw(*shaderProgram);
    }

    for (const auto& child : children) {
        child->draw(reference * (transform ? *transform : reference), camera);
    }
}

void RenderObject::initialize() {
    if (shaderProgram) {
        if (material) {
            Material::registerMaterial(*shaderProgram);
        }
        if (transform) {
            shaderProgram->registerUniform("model");
        }
        Camera::registerCamera(*shaderProgram);
    }

    for (const auto& child : children) {
        child->initialize();
    }
}

std::optional<RenderObject> RenderObjectBuilder::build() const {
    if ((!mesh || !shaderProgram)) {
        return std::nullopt;
    }

    RenderObject renderObject;
    renderObject.shaderProgram = shaderProgram;
    renderObject.mesh = mesh;
    renderObject.transform = transform;
    renderObject.material = material;
    return renderObject;
}