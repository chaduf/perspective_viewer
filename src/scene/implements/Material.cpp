#include <Material.hpp>

void Material::apply(const GLShaderProgram& shaderProgram) const {
    shaderProgram.setUniform("materialColor", color);
    for (const auto& [name, appliedTexture] : appliedTextureMap) {
        glActiveTexture(GL_TEXTURE0 + appliedTexture.slot);
        appliedTexture.texture->apply();
    }
}

void Material::unapply() const {
    for (const auto& [name, appliedTexture] : appliedTextureMap) {
        glActiveTexture(GL_TEXTURE0 + appliedTexture.slot);
        appliedTexture.texture->unapply();
    }
}

std::optional<std::shared_ptr<Texture>> Material::getTexture(std::string name) const { 
    auto it = appliedTextureMap.find(name);
    if (it != appliedTextureMap.end()) {
        return it->second.texture;
    }
    std::cerr << "Warning: Invalid texture name." << std::endl;
    return std::nullopt;
}

std::optional<int32_t> Material::getTextureSlot(std::string name) const { 
    auto it = appliedTextureMap.find(name);
    if (it != appliedTextureMap.end()) {
        return it->second.slot;
    }
    std::cerr << "Warning: Invalid texture name." << std::endl;
    return std::nullopt;
}

Material& Material::addTexture(const std::string& name, uint32_t slot, const std::shared_ptr<Texture>& texture) {
    if (slot >= NR_TEXTURE_SLOTS) {
        std::cerr << "Error: Texture slot out of range." << std::endl;
        return *this;
    }

    if (appliedTextureMap.find(name) != appliedTextureMap.end()) {
        std::cerr << "Error: Texture with name '" << name << "' is already applied." << std::endl;
        return *this;
    }

    if (appliedTextureMap.size() >= NR_TEXTURE_SLOTS) {
        std::cerr << "Error: Maximum number of textures reached." << std::endl;
        return *this;
    }

    for (const auto& [name, appliedTexture] : appliedTextureMap) {
        if (appliedTexture.slot == slot) {
            std::cerr << "Error: Texture slot " << slot << " is already occupied by '" << name << "'." << std::endl;
            return *this;
        }
    }

    appliedTextureMap[name] = AppliedTexture{ texture, slot };
    return *this;
}

void Material::registerMaterial(GLShaderProgram& shaderProgram) {
    shaderProgram.registerUniform("materialColor");
}
