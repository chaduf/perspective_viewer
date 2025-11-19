#include <GLShader.hpp>
#include <GLUtils.hpp>

#include <iostream>
#include <fstream>
#include <string>

namespace Perspective::render::GLES {
        
    GLShader::GLShader(const SourceCodeString& source, GLenum stage) 
        : shader_([stage] () { return glCreateShader(stage); }, glDeleteShader) {
                
        if (!setSource_(source) || !compile_()) {
            std::cerr << "Failed to create shader." << std::endl;
        }
    }

    GLShader::GLShader(const FileNameString& fileName, GLenum stage) 
        : shader_([stage] () { return glCreateShader(stage); }, glDeleteShader) {

        if (!setSource_(fileName) || !compile_()) {
            std::cerr << "Failed to create shader." << std::endl;
        }
    }

    GLShader::~GLShader() {
        // Destructor implementation
    }

    bool GLShader::setSource_(const SourceCodeString& sourceCode) {
        const char* shaderSourceCode = sourceCode.data();
        glShaderSource(shader_.get(), 1, &shaderSourceCode, nullptr);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "Error setting shader source: " << error << std::endl;
            return false;
        }
        return true;
    }

    bool GLShader::setSource_(const FileNameString& fileName) {
        // Read shader code from file
        std::ifstream file(fileName.get());
        if (!file.is_open()) {
            std::cerr << "Failed to open shader file: " << fileName.get() << std::endl;
            return false;
        }

        std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return setSource_(SourceCodeString(source));
    }

    bool GLShader::compile_() {
        glCompileShader(shader_.get());

        // Compilation check
        GLint success;
        glGetShaderiv(shader_.get(), GL_COMPILE_STATUS, &success);
        if (!success) {
            std::string infoLog(512, '\0');
            glGetShaderInfoLog(shader_.get(), 512, nullptr, infoLog.data());
            std::cerr << "Error compiling shader: " << infoLog << std::endl;
            return false;
        }
        return true;
    }
} // namespace Perspective::render::GLES