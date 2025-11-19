#pragma once

namespace Perspective {

    class SceneView {
    public:
        SceneView() = default;
        ~SceneView() = default;

        SceneView(const SceneView&) = default;
        SceneView& operator=(const SceneView&) = default;

        SceneView(SceneView&&) noexcept = default;
        SceneView& operator=(SceneView&&) noexcept = default;
    };

} // namespace Perspective

