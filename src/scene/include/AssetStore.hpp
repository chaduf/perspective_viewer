#pragma once

#include <Geometry.hpp>
#include <Stage.hpp>
#include <Technic.hpp>

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <optional>

namespace Perspective::scene {

class AssetStore {
public:
    AssetStore() = default;
    AssetStore(const AssetStore&) = delete;
    AssetStore& operator=(const AssetStore&) = delete;
    AssetStore(AssetStore&&) = delete;
    AssetStore& operator=(AssetStore&&) = delete;
    ~AssetStore() = default;

    std::string addTechnic(Technic technic);
    void removeTechnic(const std::string& id);
    std::optional<std::reference_wrapper<const Technic>> getTechnic(const std::string& id) const;
    std::optional<std::reference_wrapper<Technic>> getTechnic(const std::string& id);

    std::string addStage(Stage stage);
    void removeStage(const std::string& id);
    std::optional<std::reference_wrapper<const Stage>> getStage(const std::string& id) const;
    std::optional<std::reference_wrapper<Stage>> getStage(const std::string& id);

    std::string addGeometry(Geometry geometry);
    void removeGeometry(const std::string& id);
    std::optional<std::reference_wrapper<const Geometry>> getGeometry(const std::string& id) const;
    std::optional<std::reference_wrapper<Geometry>> getGeometry(const std::string& id);

private:
    std::string generateId_() const;

    std::unordered_map<std::string, Technic> technics_;
    std::unordered_map<std::string, Stage> stages_;
    std::unordered_map<std::string, Geometry> geometries_;
};

} // namespace Perspective::scene
