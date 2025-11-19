#pragma once

#include <string>
#include <optional>

namespace Perspective::scene {

    class Renderable {
    public:
        Renderable() = default;
        Renderable(const Renderable&) = default;
        Renderable& operator=(const Renderable&) = default;
        Renderable(Renderable&&) noexcept = default;
        Renderable& operator=(Renderable&&) noexcept = default;

        bool operator==(const Renderable& other) const noexcept = default;
        bool operator!=(const Renderable& other) const noexcept = default;

        virtual ~Renderable() = default;

        // Getters
        const std::optional<std::string>& getGeometryId() const noexcept { return geometryId_; }
        const std::optional<std::string>& getTechnicId() const noexcept { return technicId_; }

        // Setters
        Renderable& setGeometryId(std::string id) noexcept;
        Renderable& setTechnicId(std::string id) noexcept;
        Renderable& initialize();

    private:
        std::optional<std::string> geometryId_ = std::nullopt;
        std::optional<std::string> technicId_ = std::nullopt;
    };
} // namespace Perspective::scene
