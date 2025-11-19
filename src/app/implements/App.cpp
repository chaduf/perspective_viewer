#include <App.hpp>
#include <StrongString.hpp>

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

namespace Perspective
{
    // Temporary functions
    void __loadCubeGeometry__() {
        std::cerr << "Loading cube geometry for testing purposes." << std::endl;
        // Temporary function to load a cube geometry into the scene
        // In a real application, this would load from a model file or generate procedurally
    }


    App::App()
        : status_(Status::Uninitialized),
          window_(nullptr, SDL_DestroyWindow),
          graphicContext_(nullptr, SDL_GL_DestroyContext),
          renderer_(nullptr),
          sceneController_(std::make_unique<Scene::SceneController>())
    {
        initialize();
    }

    App::~App() {}

    void App::initialize()
    {
        std::cerr << "Starting application initialization." << std::endl;

        if (!configureOpenGL_() 
            || !initializeSDL_() 
            || !createWindow_() 
            || !createGraphicsContext_())
        {
            std::cerr << "App initialization failed." << std::endl;
            cleanup();
            return;
        }

        status_ = Status::Initialized;
        std::cerr << "All components initialized successfully." << std::endl;
    }

    bool App::initializeSDL_()
    {
        std::cerr << "Initializing SDL3 subsystems." << std::endl;
        bool success = SDL_InitSubSystem(SDL_INIT_VIDEO);
        if (!success)
        {
            std::cerr << "Failed to initialize SDL3: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    };

    bool App::createWindow_()
    {
        window_.reset(SDL_CreateWindow("Perspective Viewer", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
        if (window_.get() == nullptr)
        {
            std::cerr << "Failed to create SDL3 window: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    };

    bool App::configureOpenGL_()
    {
        std::cerr << "Configuring OpenGL attributes." << std::endl;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        // Attributs supplémentaires pour forcer le double buffering
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        return true;
    };

    bool App::createGraphicsContext_()
    {
        graphicContext_.reset(SDL_GL_CreateContext(window_.get()));
        if (graphicContext_.get() == nullptr)
        {
            std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
            return false;
        }

        // ✅ Check Attributes
        int major, minor, depthSize, doubleBuffer, profile;
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
        SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &depthSize);
        SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &doubleBuffer);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);

        std::cerr << "OpenGL Context created:" << std::endl;
        std::cerr << "  Version: " << major << "." << minor << std::endl;
        std::cerr << "  Depth buffer: " << depthSize << " bits" << std::endl;
        std::cerr << "  Double buffer: " << (doubleBuffer ? "YES" : "NO") << std::endl;
        std::cerr << "  Profile: " << (profile == SDL_GL_CONTEXT_PROFILE_ES ? "ES" : "Desktop") << std::endl;

        // Vérifier avec OpenGL directement
        std::cerr << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cerr << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        // Set VSync
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
            std::cerr << "Warning: Unable to set VSync: " << SDL_GetError() << std::endl;
        }
        else
        {
            std::cerr << "VSync enabled - framerate locked to display refresh rate" << std::endl;
        }

        return true;
    };

    void App::handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) && status_ == Status::Running)
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                std::cerr << "Received quit event." << std::endl;
                stop();
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                std::cerr << "Received window resized event." << std::endl;
                glViewport(0, 0, event.window.data1, event.window.data2);
                break;
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key)
                {
                case SDLK_ESCAPE:
                    std::cerr << "Received ESC key down event." << std::endl;
                    stop();
                    break;
                default:
                    std::cerr << "Received key down event: " << event.key.key << std::endl;
                    break;
                }
                break;
            }
        }
    }

    void App::run()
    {
        __loadCubeGeometry__(); // Temporary for testing

        status_ = Status::Running;

        // Main loop implementation
        loop();

        std::cerr << "Application stopped." << std::endl;
    }

    void App::loop()
    {
        uint64_t frameCount = 0;
        while (status_ == Status::Running)
        {
            logFrameRate_();
            // std::cerr << "Frame: " << frameCount << std::endl;

            uint32_t frameStart = SDL_GetTicks();

            handleEvents();
            update();

            uint32_t frameEnd = SDL_GetTicks();
            uint32_t frameTime = frameEnd - frameStart;

            if (frameTime < FRAME_TIME)
            {
                SDL_Delay(FRAME_TIME - frameTime);
            }

            frameCount++;
        }
    }

    void App::logFrameRate_()
    {
        static uint32_t frameCount = 0;
        static uint32_t lastTime = SDL_GetTicks();
        frameCount++;

        uint32_t currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= 1000)
        {
            std::cerr << "FPS: " << frameCount << std::endl;
            frameCount = 0;
            lastTime = currentTime;
        }
    }

    void App::update()
    {
        renderer_->render(sceneController_->getScene());
        SDL_GL_SwapWindow(window_.get());
    }

    void App::stop()
    {
        std::cerr << "Stopping application request." << std::endl;
        status_ = Status::Stopped;
    }

    void App::cleanup() {
        window_.reset();
        graphicContext_.reset();
        SDL_Quit();
    }

    void App::setRenderer(std::unique_ptr<render::IRenderer> renderer) {
        std::cerr << "Setting renderer in App." << std::endl;
        renderer_ = std::move(renderer);
    }

} // namespace Perspective
