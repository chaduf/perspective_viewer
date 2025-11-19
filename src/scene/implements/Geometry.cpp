#include <Geometry.hpp>

#include <iostream>

namespace Perspective::scene {
// DataBuffer::DataBuffer(std::vector<T> data, GLenum target, GLenum usage)
//     : target(target), usage(usage), size(data.size()) {
    
// }

// DataBuffer::~DataBuffer() {
//     glDeleteBuffers(1, &ID);
// }

// Geometry::Geometry() : 
//     VAO(glGenVertexArrays, glDeleteVertexArrays),
//     VBO(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
//     EBO(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)
// {
//     std::cerr << "Geometry move constructor called" << std::endl;
//     std::cerr << "Moved VAO: " << VAO.get() << std::endl;
//     std::cerr << "Moved VBO: " << VBO.get() << std::endl;
//     std::cerr << "Moved EBO: " << EBO.get() << std::endl;
// }

void Geometry::setup(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, Topology topology) {
    if (vertices.empty() || indices.empty()) {
        std::cerr << "Cannot setup mesh: Empty vertices or indices in Geometry::setup()" << std::endl;
        return;
    }

    this->vertices_ = vertices;
    this->indices_ = indices;
    this->topology_ = topology;
}

//     // Enable vertex attribute array
//     glBindVertexArray(VAO.get());

//     // Load data to buffer
//     VBO.loadData(vertices);
//     EBO.loadData(indices);

//     // Set vertex position attribute pointers
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
//     glEnableVertexAttribArray(0);

//     // Set vertex texture coordinate attribute pointers
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
//     glEnableVertexAttribArray(1);

//     // Disable Vertex attribute array
//     glBindVertexArray(0);

//     this->mode = mode;
//     std::cerr << "Geometry setup complete: \n\tVAO: { id: " << VAO.get()<< " }" << std::endl;
//     std::cerr << "\tVBO: { id: " << VBO.get()<< ", size: " << VBO.getSize() << " }" << std::endl;
//     std::cerr << "\tEBO: { id: " << EBO.get()<< ", size: " << EBO.getSize() << " }" << std::endl;
// }

// void Geometry::draw(const GLShaderProgram& shaderProgram) const {
//     if (VAO.get() == 0 || VBO.get() == 0) {
//         std::cerr << "Cannot display mesh: Corrupted buffers in Geometry::draw()" << std::endl;
//         return;
//     }

//     glBindVertexArray(VAO.get());
//     GLUtils::checkedCall("glDrawElements", glDrawElements, toGLenum(mode), EBO.getSize(), GL_UNSIGNED_INT, (const void*)0);
//     glBindVertexArray(0);
// }

} // namespace Perspective::scene