#pragma once

#include <SDL3/SDL.h>
#include <GLES3/gl3.h>

#include <memory>
#include <type_traits>
#include <utility>

#include <IRenderer.hpp>
#include <SceneController.hpp>

namespace Perspective
{
    class App {
        public:
        enum class Status {
            Uninitialized,
            Initialized,
            Running,
            Stopped,
            Error
        };
        
        // Public Constructors
        App();
        App(const App&) = delete;
        App& operator=(const App&) = delete;
        
        App(App&&) noexcept = default;
        App& operator=(App&&) noexcept = default;
        
        // Destructor
        ~App();
        
        Status getStatus() const { return status_; }
        
        // Public methods
        void initialize();
        void run();
        void loop();
        void handleEvents();
        void update();
        void stop();
        void cleanup();

        // Setters
        void setRenderer(render::IRenderer&& renderer);
        void setRenderer(std::unique_ptr<render::IRenderer> renderer);

        void setScene(Scene::Scene&& scene);
        void setScene(std::unique_ptr<Scene::Scene> scene);

        // Commands

    private:

        // Attributes
        Status status_;
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
        std::unique_ptr<std::remove_pointer_t<SDL_GLContext>, decltype(&SDL_GL_DestroyContext)> graphicContext_;
        std::unique_ptr<render::IRenderer> renderer_;
        std::unique_ptr<Scene::SceneController> sceneController_;
        
        static constexpr uint32_t FRAME_TIME = 16; // Approx. 60 FPS


        // Private methods
        // initialization methods
        bool configureOpenGL_();
        bool createGraphicsContext_();
        bool initializeSDL_();
        bool createWindow_();

        // Debug methods
        void logFrameRate_();
    };

} // namespace Perspective
