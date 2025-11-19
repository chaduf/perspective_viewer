#pragma once

#include <SceneTypes.hpp>

#include <string>
#include <utility>

namespace Perspective::scene {

class Stage {
public:
    Stage() = default;
    Stage(StageType type, std::string source);

    virtual ~Stage() = default;

    StageType getType() const { return type_; }
    const std::string& getSource() const { return source_; }

protected:
    StageType type_{StageType::VertexProcessing};
    std::string source_;
};

} // namespace Perspective::scene
