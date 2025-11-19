#pragma once

namespace Perspective::scene {

enum class Topology {
    Points,
    LineStrip,
    LineLoop,
    Lines,
    TriangleStrip,
    TriangleFan,
    Triangles,
};

enum class StageType {
    VertexProcessing,
    FragmentProcessing,
};

} // namespace Perspective::scene
