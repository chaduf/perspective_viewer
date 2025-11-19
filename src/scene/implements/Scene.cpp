#include <Scene.hpp>

#include <vector>
#include <iostream>

namespace Perspective::scene
{

    Scene::Scene() :
        root{.node = Node::create()},
        rootId(core::UuidGenerator::generate())
    {
        nodeWrappers.emplace(rootId, NodeWrapper{
            .node = root.node, 
            .parentId = std::nullopt, 
            .childrenIds = {}
        });
    }

    Scene::~Scene()
    {
        // Destructor implementation
    }

    void Scene::initialize()
    {
        // Ininitatialization code
    }

    std::optional<std::string> Scene::addNode(const std::string &name, std::shared_ptr<Node> node, std::optional<std::string> parentId)
    {
        const std::string resolvedParentId = parentId.value_or(rootId);

        auto parentIt = nodeWrappers.find(resolvedParentId);
        if (parentIt == nodeWrappers.end())
        {
            std::cerr << "Parent ID '" << resolvedParentId << "' not found. Cannot add node '" << name << "'." << std::endl;
            return std::nullopt;
        }

        auto parent = parentIt->second.node;
        parent->addChild(name, node);

        // Verify that the child was added successfully
        if (parent->getChild(name).lock() != node)
        {
            std::cerr << "Failed to add node '" << name << "' to parent with ID '" << resolvedParentId << "'." << std::endl;
            return std::nullopt;
        }

        std::string id = core::UuidGenerator::generate();
        nodeWrappers.emplace(id, NodeWrapper{.node = node, .parentId = resolvedParentId});
        parentIt->second.addChildId(id);

        std::function<void(std::string, std::shared_ptr<Node>)> registerChildren = 
            [this, &registerChildren](std::string id, std::shared_ptr<Node> nodePtr) {
            for (const auto &[childName, childPtr] : nodePtr->getChildren()) {
                std::string childId = core::UuidGenerator::generate();
                if (auto it = nodeWrappers.find(id); it != nodeWrappers.end()) {
                    it->second.addChildId(childId);
                }
                nodeWrappers.emplace(childId, NodeWrapper(childPtr, id));
                registerChildren(childId, childPtr);
            }
        };

        registerChildren(id, node);
        return id;
    }

    void Scene::removeNode(const std::string &id)
    {
        auto nodeIt = nodeWrappers.find(id);
        if (nodeIt == nodeWrappers.end()) {
            std::cerr << "Node ID '" << id << "' not found. Cannot remove node." << std::endl;
            return;
        }

        if (id == rootId) {
            std::cerr << "Cannot remove root node." << std::endl;
            return;
        }

        auto node = nodeIt->second.node;
        const auto& parentId = nodeIt->second.parentId;
        if (!parentId) {
            std::cerr << "Node '" << id << "' has no registered parent. Cannot remove node." << std::endl;
            return;
        }

        std::function<void(const std::string&)> unregisterChildren = [this, &unregisterChildren](const std::string& nodeId) {
            if (auto children = getChildrenIds(nodeId)) {
                for (const auto& childId : *children) {
                    unregisterChildren(childId);
                }
            }
            nodeWrappers.erase(nodeId);
        };

        auto parentIt = nodeWrappers.find(*parentId);
        if (parentIt == nodeWrappers.end()) {
            std::cerr << "Parent ID '" << *parentId << "' not found. Cannot detach node '" << id << "'." << std::endl;
            return;
        }

        parentIt->second.node->removeChild(node);
        parentIt->second.removeChildId(id);
        unregisterChildren(id);
    }

    std::optional<std::shared_ptr<Node>> Scene::getNode(const std::string &id) const
    {
        auto it = nodeWrappers.find(id);
        if (it != nodeWrappers.end()) {
            return it->second.node;
        }
        return std::nullopt;
    }

    std::optional<std::vector<std::string>> Scene::getChildrenIds(const std::string &id) const
    {
        auto it = nodeWrappers.find(id);
        if (it != nodeWrappers.end()) {
            return it->second.childrenIds;
        }
        return std::nullopt;
    }

    void Scene::traverse(const std::function<void(Node &)> &callback)
    {
        root.node->traverse(callback);
    }
        

    void Scene::attachRenderableToNode(const std::string& nodeId, Renderable&& renderable) {
        auto it = nodeWrappers.find(nodeId);
        if (it == nodeWrappers.end()) {
            std::cerr << "Node ID '" << nodeId << "' not found. Cannot add renderable." << std::endl;
            return;
        }

        it->second.node->attachRenderable(std::forward<Renderable>(renderable));
    }
} // namespace Perspective::scene
