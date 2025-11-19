#pragma once

#include <GLUtils.hpp>
#include <StrongString.hpp>

#include <string>
#include <GLES3/gl3.h>

namespace Perspective::render::GLES {
    class GLShader {
    public:
        GLShader(const SourceCodeString& source, GLenum stage);
        GLShader(const FileNameString& source, GLenum stage);
        ~GLShader();

        GLShader(const GLShader&) = delete;
        GLShader& operator=(const GLShader&) = delete;

        GLShader(GLShader&& other) noexcept = default;
        GLShader& operator=(GLShader&& other) noexcept = default;

        GLuint getID() const { return shader_.get(); }
        
    private:
        GLUtils::SingleGLResource shader_;

        // Private functions
        bool setSource_(const SourceCodeString& sourceCode);
        bool setSource_(const FileNameString& fileName);
        bool compile_();
    };
} // namespace Perspective::render::GLES