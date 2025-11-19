#include <Technic.hpp>

namespace Perspective::scene {

void Technic::addStage(const std::string& id, Stage stage)
{
    stages_[id] = std::move(stage);
}

bool Technic::hasStage(const std::string& id) const
{
    return stages_.find(id) != stages_.end();
}

const Stage* Technic::getStage(const std::string& id) const
{
    const auto it = stages_.find(id);
    return it != stages_.end() ? &it->second : nullptr;
}

} // namespace Perspective::scene
