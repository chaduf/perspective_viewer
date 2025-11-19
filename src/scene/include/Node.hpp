#pragma once

#include <Transform.hpp>
#include <Renderable.hpp>

#include <memory>
#include <optional>
#include <unordered_map>
#include <string>
#include <functional>

namespace Perspective::scene { 

        // Minimal scene graph node base class — see docs/Node.md for details.
    class Node : public std::enable_shared_from_this<Node>
    {
    public:
        /** Factory: create a shared_ptr<Node>. */
        template <typename... Args>
        static std::shared_ptr<Node> create(Args &&...args)
        {
            auto instance = std::make_shared<Node>(std::forward<Args>(args)...);
            return instance;
        }

        Node() = default;
        Node(const Node &other) = delete;
        Node &operator=(const Node &other) = delete;
        Node(Node &&other) = delete;
        Node &operator=(Node &&other) = delete;
        virtual ~Node() = default;

        /** Deep-equality: transform and children. */
        bool operator==(const Node &other) const noexcept;

        /** Deep-inequality: transform and children. */
        bool operator!=(const Node &other) const noexcept
        {
            return !(*this == other);
        }

        // Getters / setters (brief comments only)
        Transform &getTransform() noexcept { return transform_; }
        const Transform &getTransform() const noexcept { return transform_; }
        Node &setTransform(Transform &&t) noexcept
        {
            transform_ = std::move(t);
            return *this;
        }
        Node &setTransform(const Transform &t) noexcept
        {
            transform_ = t;
            return *this;
        }

        // Child management (short docs)
        // Add child, caller cedes ownership (expects shared_ptr). Sets child's parent_.
        Node &addChild(const std::string &name, std::shared_ptr<Node> child);

        // Remove child by name, if present; clears child's parent_.
        Node &removeChild(const std::string &name);
        Node &removeChild(std::shared_ptr<Node> child);

        Node &attachRenderable(Renderable &&renderable);
        
        // Remove and return ownership of child (returns nullptr if absent).
        std::shared_ptr<Node> takeChild(const std::string &name);

        // Return non‑owning weak_ptr to child; lock() to obtain shared_ptr.
        std::weak_ptr<Node> getChild(const std::string &name) noexcept;

        // Return map of shared_ptr to all children.
        const std::unordered_map<std::string, std::shared_ptr<Node>> getChildren() const noexcept;
        Renderable& getRenderable() noexcept { return renderable_; }
        const Renderable& getRenderable() const noexcept { return renderable_; }

        // Return non‑owning weak_ptr to parent; lock() to obtain shared_ptr.
        std::weak_ptr<Node> getParent() noexcept;

        // Deep clone subtree; returned root has parent_ cleared.
        std::shared_ptr<Node> clone() const;

        // Traverse subtree, applying func to each node (including this).
        Node &traverse(std::function<void(Node &)> func) noexcept;

        bool isRoot() const noexcept { return parent_.expired(); }

        bool isLeaf() const noexcept { return children_.empty(); }

        bool checkNameExistence(const std::string &name) const noexcept;
        static bool checkNameFormat(const std::string &name) noexcept;

    private:
        Transform transform_;
        Renderable renderable_;
        std::weak_ptr<Node> parent_;
        std::unordered_map<std::string, std::shared_ptr<Node>> children_;
    };
} // namespace Perspective::scene
