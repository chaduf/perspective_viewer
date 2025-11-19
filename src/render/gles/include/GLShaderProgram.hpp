#pragma once

#include <GLUtils.hpp>
#include <GLShader.hpp>
#include <ITechnic.hpp>

#include <GLES3/gl3.h>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <string>
#include <type_traits>

namespace Perspective::render::GLES {

class GLShaderProgram : ITechnic{
public:
    GLShaderProgram();
    GLShaderProgram(const GLShader& vertexShader, const GLShader& fragmentShader);
    GLShaderProgram(GLShader&& vertexShader, GLShader&& fragmentShader);

    GLShaderProgram(const GLShaderProgram&) = delete;
    GLShaderProgram& operator=(const GLShaderProgram&) = delete;

    GLShaderProgram(GLShaderProgram&& other) noexcept = default;
    GLShaderProgram& operator=(GLShaderProgram&& other) noexcept = default;

    ~GLShaderProgram();

    void addShader(const GLShader& shader);
    void link();

    bool isProgram() const;
    bool isLinked() const;

    bool isValid() const;

    void registerUniform(const std::string& name);
    uint32_t getUniformLocation(const std::string& name) const;

    template<typename T>
    void setUniform(const std::string& name, const T& value) const {
        uint32_t location = getUniformLocation(name);
        if (location != -1) {
            if constexpr (std::is_same_v<T, int>) {
                glUniform1i(location, value);
            } else if constexpr (std::is_same_v<T, float>) {
                glUniform1f(location, value);
            } else if constexpr (std::is_same_v<T, glm::vec2>) {
                glUniform2fv(location, 1, glm::value_ptr(value));
            } else if constexpr (std::is_same_v<T, glm::vec3>) {
                glUniform3fv(location, 1, glm::value_ptr(value));
            } else if constexpr (std::is_same_v<T, glm::vec4>) {
                glUniform4fv(location, 1, glm::value_ptr(value));
            } else if constexpr (std::is_same_v<T, glm::mat4>) {
                glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
            } else {
                static_assert(sizeof(T) == 0, "Unsupported uniform type");
            }
        }
    }
    
    // Getters
    GLuint getId() const { return id.get(); }

    // override ITechnic methods
    void setup() override;
    void apply() const override;
    void teardown() override;

private:
    // Attributes
    GLUtils::SingleGLResource id;
    std::map<std::string, GLint> uniformLocations;
    };
} // namespace Perspective::render::GLES