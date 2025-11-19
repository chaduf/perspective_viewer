
#include <StrongString.hpp>

#include <GLES3/gl3.h>
#include <GLUtils.hpp>

#include <string>

class Texture {
public:
    Texture(const FileNameString& filePath);
    ~Texture() = default;

    void apply() const;
    void unapply() const;

private:
    GLUtils::SingleGLResource textureID;
    int32_t width;
    int32_t height;
    int32_t channels;
};