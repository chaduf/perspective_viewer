#pragma once

#include <Stage.hpp>

#include <string>
#include <unordered_map>
#include <utility>

namespace Perspective::scene {

class Technic {
public:
    Technic() = default;
    virtual ~Technic() = default;

    void addStage(const std::string& id, Stage stage);
    bool hasStage(const std::string& id) const;
    const Stage* getStage(const std::string& id) const;
    const std::unordered_map<std::string, Stage>& getStages() const { return stages_; }

protected:
    std::unordered_map<std::string, Stage> stages_;
};

} // namespace Perspective::scene
