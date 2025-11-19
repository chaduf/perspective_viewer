#include <Texture.hpp>
#include <ShaderProgram.hpp>

#include <memory>
#include <vector>
#include <optional>

enum class TextureType {
    Diffuse,
    Specular,
    Normal,
    Height,
    Custom
};

struct AppliedTexture {
    std::shared_ptr<Texture> texture;
    uint32_t slot;
};

class MaterialGuard;
class Material {
    friend class MaterialGuard;
public:
    // Maximum number of textures
    constexpr static int32_t NR_TEXTURE_SLOTS = 16;

    // Constructor
    Material(): color(1.0f, 1.0f, 1.0f), appliedTextureMap() {}
    ~Material() = default;

    void apply(const GLShaderProgram& shaderProgram) const;
    void unapply() const;
    
    const glm::vec3& getColor() const { return color; }
    glm::vec3& getColor() { return color; }
    std::optional<std::shared_ptr<Texture>> getTexture(std::string name) const;
    std::optional<int32_t> getTextureSlot(std::string name) const;

    // Material configuration
    Material& setColor(const glm::vec3& color) { this->color = color; return *this; }
    Material& addTexture(const std::string& name, uint32_t slot, const std::shared_ptr<Texture>& texture);

    static void registerMaterial(GLShaderProgram& shaderProgram);

private:
    glm::vec3 color;
    std::map<std::string, AppliedTexture> appliedTextureMap;
};