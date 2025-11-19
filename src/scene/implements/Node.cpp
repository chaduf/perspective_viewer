#include<Node.hpp>

#include <regex>
#include <string>
#include <iostream>

namespace Perspective::scene {

    bool Node::operator==(const Node& other) const noexcept {
        if (transform_ != other.transform_) return false;
        if (renderable_ != other.renderable_) return false;
        for (const auto& [name, child] : children_) {
            auto it = other.children_.find(name);
            if (it == other.children_.end() || !(*(it->second) == *child)) {
                return false;
            }
        }
        return true;
    }

    std::weak_ptr<Node>Node::getChild(const std::string& name) noexcept {
        auto it = children_.find(name);
        if (it != children_.end()) {
            return it->second->weak_from_this();
        }
        return std::weak_ptr<Node>();
    }

    const std::unordered_map<std::string, std::shared_ptr<Node>> Node::getChildren() const noexcept {
        return children_;
    }

    std::weak_ptr<Node> Node::getParent() noexcept {
        return parent_;
    }

    std::shared_ptr<Node> Node::takeChild(const std::string& name) {
        auto it = children_.find(name);
        if (it != children_.end()) {
            auto child = it->second;
            child->parent_.reset();
            children_.erase(it);
            return child;
        }
        return nullptr;
    }

    Node& Node::removeChild(const std::string& name) {
        takeChild(name);
        return *this;
    }

    Node& Node::removeChild(std::shared_ptr<Node> child) {
        for (auto childIt : children_) {
            if (childIt.second == child) {
                takeChild(childIt.first);
                break;
            }
        }
        return *this;
    }

    Node& Node::addChild(const std::string& name, std::shared_ptr<Node> child) {
        if (child) {
            if (!checkNameFormat(name)) {
                std::cerr << "Invalid child name format: " << name << std::endl;
                return *this; 
            }

            if (checkNameExistence(name)) {
                std::cerr << "Child name already exists: " << name << std::endl;
                return *this; 
            }

            child->parent_ = this->shared_from_this();
            children_[name] = std::move(child); // move into container
        }
        return *this;
    }

    Node& Node::attachRenderable(Renderable &&renderable) {
        renderable_ = std::move(renderable);
        return *this;
    }

    std::shared_ptr<Node> Node::clone () const {
        auto clone = std::make_shared<Node>();
        clone->transform_ = transform_;
        clone->renderable_ = renderable_;
        for (const auto& [name, child] : children_) {
            auto clonedChild = child->clone();
            clonedChild->parent_ = clone;
            clone->children_[name] = clonedChild;
        }
        return clone;
    }

    Node& Node::traverse(std::function<void(Node&)> func) noexcept {
        for (auto& [name, child] : children_) {
            if (child) {
                func(*child);
                child->traverse(func);
            }
        }
        return *this;
    }

    bool Node::checkNameExistence(const std::string &name) const noexcept {
        return children_.find(name) != children_.end();
    }

    bool Node::checkNameFormat(const std::string &name) noexcept {
        if (name.empty()) {
            return false;
        }

        std::regex pattern("^[A-Za-z_][A-Za-z0-9_-]*$");
        if (!std::regex_match(name, pattern)) {
            return false;
        }
        
        return true;
    }
} // namespace Perspective::scene