#include <Stage.hpp>

namespace Perspective::scene {

Stage::Stage(StageType type, std::string source)
    : type_(type), source_(std::move(source))
{}

} // namespace Perspective::scene
