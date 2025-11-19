#include <GLShaderProgram.hpp>
#include <GLUtils.hpp>

#include <iostream>
#include <string>
#include <memory>

namespace Perspective::render::GLES {

    GLShaderProgram::GLShaderProgram(): id(glCreateProgram, glDeleteProgram) {
        GLuint programId = id.get();
        std::cerr << "program.get() returns: " << programId << std::endl;
        std::cerr << "glIsProgram(" << programId << "): " << (glIsProgram(programId) ? "TRUE" : "FALSE") << std::endl;
    }

    GLShaderProgram::GLShaderProgram(const GLShader& vertexShader, const GLShader& fragmentShader) : GLShaderProgram() {
        addShader(vertexShader);
        addShader(fragmentShader);
    }

    GLShaderProgram::GLShaderProgram(GLShader&& vertexShader, GLShader&& fragmentShader): GLShaderProgram() {
        addShader(std::move(vertexShader));
        addShader(std::move(fragmentShader));
    }

    GLShaderProgram::~GLShaderProgram() {
        // Destructor implementation
    }

    void GLShaderProgram::addShader(const GLShader& shader) {
        glAttachShader(id.get(), shader.getID());
        
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "Error attaching shader: " << error << std::endl;
        }
    }

    void GLShaderProgram::link() {
        glLinkProgram(id.get());

        if (!isLinked()) {
            GLchar infoLog[512];
            glGetProgramInfoLog(id.get(), 512, nullptr, infoLog);
            std::cerr << "Error linking shader program: " << infoLog << std::endl;
            return;
        }

        std::cerr << "Shader program linked successfully: id " << id.get() << std::endl;
    }

    void GLShaderProgram::apply() const {
        if (!isValid()) {
            std::cerr << "Cannot apply shader program: " << id.get() << std::endl;
            return;
        }

        glUseProgram(id.get());
    }

    bool GLShaderProgram::isProgram() const {
        return glIsProgram(id.get()) == GL_TRUE;
    }

    bool GLShaderProgram::isLinked() const { 
        GLint status;
        glGetProgramiv(id.get(), GL_LINK_STATUS, &status);
        return status == GL_TRUE;
    }

    bool GLShaderProgram::isValid() const {
        return isProgram() && isLinked();
    }

    void GLShaderProgram::registerUniform(const std::string& name) {
        if (uniformLocations.find(name) != uniformLocations.end()) {
            return; // Already registered
        }
        apply();
        GLint location = glGetUniformLocation(id.get(), name.c_str());
        if (location == -1) {
            std::cerr << "Warning: Could not find uniform location for " << name << " in shader program " << id.get() << std::endl;
        } else {
            uniformLocations[name] = location;
        }
    }

    uint32_t GLShaderProgram::getUniformLocation(const std::string& name) const {
        auto it = uniformLocations.find(name);
        if (it != uniformLocations.end()) {
            return it->second;
        }
        std::cerr << "Warning: No uniform registered for " << name << std::endl;
        return -1;
    }
} // namespace Perspective::render::GLES