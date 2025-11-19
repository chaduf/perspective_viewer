#include <Texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <memory>
#include <iostream>


Texture::Texture(const FileNameString& filePath) :
        textureID(glGenTextures, glDeleteTextures),
        width(0), height(0), channels(0) {
    glBindTexture(GL_TEXTURE_2D, textureID.get());

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::unique_ptr<unsigned char, decltype(&stbi_image_free)> data(
        stbi_load(filePath.data(), &width, &height, &channels, 0), &stbi_image_free);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, static_cast<void*>(data.get()));
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture: " << filePath.get() << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::apply() const {
    glBindTexture(GL_TEXTURE_2D, textureID.get());
}

void Texture::unapply() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
