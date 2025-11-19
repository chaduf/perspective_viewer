#pragma once

#include <functional>
#include <GLES3/gl3.h>
#include <string>
#include <utility>
#include <sstream>
#include <iostream>

namespace Perspective::render::GLES::GLUtils {

    constexpr GLuint INVALID_DESCRIPTOR = 0;

    template <size_t N = 1>
    class GLResources {
    public:
        GLResources(std::function<void(GLsizei, GLuint*)> creator, std::function<void(GLsizei, GLuint*)> deleter) 
        : deleter(deleter) {
            creator(N, descriptors);
        }

        GLResources(const GLResources&) = delete;
        GLResources& operator=(const GLResources&) = delete;

        GLResources(GLResources&& other) noexcept
        : deleter(std::move(other.deleter)) {
            for (size_t i = 0; i < N; ++i) {
                descriptors[i] = other.descriptors[i];
                other.descriptors[i] = 0;
            }
            other.deleter = nullptr;
        }

        ~GLResources() {
            if (deleter) {
                deleter(N, descriptors);
            }
        }

        GLResources& operator=(GLResources&& other) noexcept {
            if (this != &other) {
                // Release current resources
                if (deleter) {
                    deleter(N, descriptors);
                }
                // Move resources from other
                for (size_t i = 0; i < N; ++i) {
                    descriptors[i] = other.descriptors[i];
                    other.descriptors[i] = 0;
                }
                deleter = std::move(other.deleter);
            }
            return *this;
        }

        GLuint get (size_t index) const { return descriptors[index]; }
        const GLuint* get() const { return descriptors; }

    private:
        GLuint descriptors[N];
        std::function<void(GLsizei, GLuint*)> deleter;
    };

    template <>
    class GLResources<1> {
    public:
        GLResources () = delete;
        GLResources(std::function<void(GLsizei, GLuint*)> creator, std::function<void(GLsizei, GLuint*)> deleter) {
            creator(1, &descriptor);
            this->deleter = [deleter](GLsizei _, GLuint* res) { deleter(1, res); };
        }

        GLResources (std::function<GLuint()> creator, std::function<void(GLuint)> deleter) {
            descriptor = creator();
            this->deleter = [deleter](GLsizei _, GLuint* res) { deleter(*res); };
        }

        GLResources(const GLResources&) = delete;
        GLResources& operator=(const GLResources&) = delete;

        GLResources(GLResources&& other) noexcept
        : deleter(std::move(other.deleter)), descriptor(other.descriptor) {
            other.descriptor = 0;
            other.deleter = nullptr;
        }

        GLResources& operator=(GLResources&& other) noexcept {
            if (this != &other) {
                // Release current resource
                if (deleter && descriptor != 0) {
                    deleter(1, &descriptor);
                }
                descriptor = other.descriptor;
                deleter = std::move(other.deleter);
                other.descriptor = 0;
            }
            return *this;
        }

        ~GLResources() {
            if (deleter && descriptor != 0) {
                deleter(1, &descriptor);
            }
        }

        GLuint get() const { return descriptor; }

    private:
        GLuint descriptor;
        std::function<void(GLsizei, GLuint*)> deleter;
    };

    using SingleGLResource = GLResources<1>;

    inline std::string getErrorString(GLuint error) {
        // Décoder l'erreur
        switch (error) {
            case GL_INVALID_ENUM:
                return "GL_INVALID_ENUM: mode is not an accepted value";
                break;
            case GL_INVALID_VALUE:
                return "GL_INVALID_VALUE: count is negative";
                break;
            case GL_INVALID_OPERATION:
                return "GL_INVALID_OPERATION: no VAO bound or no shader program";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return "GL_INVALID_FRAMEBUFFER_OPERATION: framebuffer incomplete";
                break;
            default:
                std::stringstream ss;
                ss << "Unknown error: 0x" << std::hex << error;
                return ss.str();
        }
    }

    template<typename Func, typename... Args>
    auto checkedCall(const std::string& functionName, Func function, Args&&... args) {
        auto logOpenGLError = [&]() {
            GLuint error = glGetError();
            if (error != GL_NO_ERROR) {
                std::cerr << "ERROR : " << functionName << " failed : " << getErrorString(error) << std::endl;
            }
        };

        while (glGetError() != GL_NO_ERROR) {
            std::cerr << "WARNING: Clearing previous OpenGL error before calling " << functionName << std::endl;
        }
        
        if constexpr (std::is_void_v<decltype(function(std::forward<Args>(args)...))>) {
            function(std::forward<Args>(args)...);
            logOpenGLError();
            return;
        } else {
            auto result = function(std::forward<Args>(args)...);
            logOpenGLError();
            return result;
        }

    }

    template <typename T>
    class BufferData
    {
    public:
        BufferData() = delete;
        BufferData(GLenum target, GLenum usage) : bufferObject(glGenBuffers, glDeleteBuffers), size(0), target(target), usage(usage) {}

        void loadData(const std::vector<T> &data)
        {
            glBindBuffer(target, bufferObject.get());
            glBufferData(target, data.size() * sizeof(T), data.data(), usage);
            size = data.size();
        }

        size_t getSize() const { return size; }
        GLuint get() const { return bufferObject.get(); }

    private:
        GLUtils::SingleGLResource bufferObject;
        size_t size = 0;
        GLenum target;
        GLenum usage;
    };
} // namespace Perspective::render::GLES::GLUtils