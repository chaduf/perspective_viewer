#pragma once

#include <AssetStore.hpp>
#include <Scene.hpp>

namespace Perspective::scene {

class SceneController {
public:
    SceneController() = default;
    SceneController(const SceneController&) = delete;
    SceneController& operator=(const SceneController&) = delete;
    ~SceneController() = default;

    // Getters
    Scene& getScene() { return scene_; }
    const Scene& getScene() const { return scene_; }

    // Commands to manipulate scene and assets

private:
    Scene scene_;
    AssetStore assetStore_;
};

} // namespace Perspective::scene
