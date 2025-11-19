

#include <iostream>
#include <App.hpp>
#include <GLRenderer.hpp>
#include <Scene.hpp>

int main() {
    auto app = Perspective::App();

    app.setRenderer(std::make_unique<Perspective::render::GLES::GLRenderer>());

    app.run();
    app.cleanup();

    

    return EXIT_SUCCESS;
}

