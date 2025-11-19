#pragma once

// #include <Camera.hpp>
#include <UuidGenerator.hpp>
#include <Node.hpp>
// #include <Camera.hpp>

#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>
#include <optional>

namespace Perspective::scene {

    class Scene {

    struct NodeWrapper {
        std::shared_ptr<Node> node = nullptr;
        std::optional<std::string> parentId = std::nullopt;
        std::vector<std::string> childrenIds = {};

        NodeWrapper& addChildId(const std::string& childId) {
            childrenIds.push_back(childId);
            return *this;
        }

        NodeWrapper& removeChildId(const std::string& childId) {
            childrenIds.erase(std::remove(childrenIds.begin(), childrenIds.end(), childId), childrenIds.end());
            return *this;
        }
    };

    public:
        Scene();
        ~Scene();

        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(Scene&&) = delete;

        void initialize();

        std::string getRootId() const { return rootId; }

        std::optional<std::string> addNode(const std::string& name, std::shared_ptr<Node> node, std::optional<std::string> parentId = std::nullopt);
        void removeNode(const std::string& id);
        std::optional<std::shared_ptr<Node>> getNode(const std::string& id) const;
        std::optional<std::vector<std::string>> getChildrenIds(const std::string& id) const;
        size_t getNodeCount() const { return nodeWrappers.size(); }

        void traverse(const std::function<void(Node&)>& callback);

        void attachRenderableToNode(const std::string& nodeId, Renderable&& renderable);

    private:
        NodeWrapper root;
        std::string rootId;
        std::unordered_map<std::string, NodeWrapper> nodeWrappers = {};
    };

} // namespace Perspective::scene
