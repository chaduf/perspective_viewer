#include <AssetStore.hpp>

#include <UuidGenerator.hpp>

namespace Perspective::scene {

std::string AssetStore::addTechnic(Technic technic)
{
    auto id = generateId_();
    technics_.emplace(id, std::move(technic));
    return id;
}

void AssetStore::removeTechnic(const std::string& id)
{
    technics_.erase(id);
}

std::optional<std::reference_wrapper<const Technic>> AssetStore::getTechnic(const std::string& id) const
{
    const auto it = technics_.find(id);
    if (it != technics_.end())
    {
        return std::cref(it->second);
    }
    return std::nullopt;
}

std::optional<std::reference_wrapper<Technic>> AssetStore::getTechnic(const std::string& id)
{
    const auto it = technics_.find(id);
    if (it != technics_.end())
    {
        return std::ref(it->second);
    }
    return std::nullopt;
}

std::string AssetStore::addStage(Stage stage)
{
    auto id = generateId_();
    stages_.emplace(id, std::move(stage));
    return id;
}

void AssetStore::removeStage(const std::string& id)
{
    stages_.erase(id);
}

std::optional<std::reference_wrapper<const Stage>> AssetStore::getStage(const std::string& id) const
{
    const auto it = stages_.find(id);
    if (it != stages_.end())
    {
        return std::cref(it->second);
    }
    return std::nullopt;
}

std::optional<std::reference_wrapper<Stage>> AssetStore::getStage(const std::string& id)
{
    const auto it = stages_.find(id);
    if (it != stages_.end())
    {
        return std::ref(it->second);
    }
    return std::nullopt;
}

std::string AssetStore::addGeometry(Geometry geometry)
{
    auto id = generateId_();
    geometries_.emplace(id, std::move(geometry));
    return id;
}

void AssetStore::removeGeometry(const std::string& id)
{
    geometries_.erase(id);
}

std::optional<std::reference_wrapper<const Geometry>> AssetStore::getGeometry(const std::string& id) const
{
    const auto it = geometries_.find(id);
    if (it != geometries_.end()) {
        return std::cref(it->second);
    }
    return std::nullopt;
}

std::optional<std::reference_wrapper<Geometry>> AssetStore::getGeometry(const std::string& id)
{
    const auto it = geometries_.find(id);
    if (it != geometries_.end()) {
        return std::ref(it->second);
    }
    return std::nullopt;
}

std::string AssetStore::generateId_() const
{
    return core::UuidGenerator::generate();
}

} // namespace Perspective::scene
