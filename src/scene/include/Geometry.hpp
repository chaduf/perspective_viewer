#pragma once

#include <SceneTypes.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace Perspective::scene {

    struct Vertex {
        glm::vec3 position;
        // GLfloat color[3];
        // GLfloat normal[3];
        glm::vec2 texCoord;
    };

    class Geometry {
    public:

        Geometry() = default;
        Geometry(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, Topology topology) {
            setup(vertices, indices, topology);
        }
        Geometry(const Geometry&) = delete;
        Geometry& operator=(const Geometry&) = delete;

        Geometry(Geometry&& other) = default;
        Geometry& operator=(Geometry&& other) = default;

        ~Geometry() = default;

        void setup(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, Topology topology);
        // void draw(const GLShaderProgram& shaderProgram) const;

        // Getters
        const std::vector<Vertex>& getVertices() const { return vertices_; }
        const std::vector<uint32_t>& getIndices() const { return indices_; }
        Topology getTopology() const { return topology_; }

    private:
        std::vector<Vertex> vertices_;
        std::vector<uint32_t> indices_;
        Topology topology_ = Topology::Triangles;
        bool dirty_ = false;
    };
} // namespace Perspective::scene
