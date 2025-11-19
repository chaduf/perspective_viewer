#include <gtest/gtest.h>

#include <Node.hpp>
#include <Transform.hpp>

#include <glm/glm.hpp>

#include <optional>
#include <memory>

using namespace Perspective::scene;

TEST(NodeTest, AddChild) {
    auto parent = Node::create();
    auto copiedChild = Node::create();
    auto movedChild = Node::create();

    // add child (child is moved into parent internals)
    parent->addChild("copiedChild", copiedChild);
    parent->addChild("movedChild", std::move(movedChild));

    auto fetchedCopied = parent->getChild("copiedChild");
    auto fetchedMoved = parent->getChild("movedChild");
    auto fetchedNotExistent = parent->getChild("nonexistent");
    ASSERT_EQ(fetchedCopied.lock(), copiedChild);
    ASSERT_EQ(fetchedCopied.lock()->getParent().lock(), parent);
    ASSERT_NE(fetchedMoved.lock(), nullptr);
    ASSERT_EQ(fetchedMoved.lock()->getParent().lock(), parent);
    ASSERT_TRUE(fetchedNotExistent.expired());

    // remove child
    parent->removeChild("movedChild");
    auto takenChild = parent->takeChild("copiedChild");

    auto fetchedAfterRemove = parent->getChild("movedChild");
    ASSERT_EQ(fetchedAfterRemove.lock(), nullptr);
    
    auto fetchedAfterTake = parent->getChild("copiedChild");
    ASSERT_EQ(fetchedAfterTake.lock(), nullptr);
    ASSERT_EQ(takenChild, copiedChild);
    ASSERT_EQ(takenChild->getParent().lock(), nullptr);
}

TEST(NodeTest, Clone) {
    auto root = Node::create();
    auto child1 = Node::create();
    auto child2 = Node::create();
    auto child21 = Node::create();
    auto child22 = Node::create();

    child1->getTransform().setPosition(glm::vec3(1.0f, 2.0f, 3.0f));
    child2->getTransform().setPosition(glm::vec3(4.0f, 5.0f, 6.0f));
    child21->getTransform().setPosition(glm::vec3(7.0f, 8.0f, 9.0f));
    child22->getTransform().setPosition(glm::vec3(10.0f, 11.0f, 12.0f));

    root->addChild("child1", child1);
    root->addChild("child2", child2);
    child2->addChild("child21", child21);
    child2->addChild("child22", child22);

    auto clonedRoot = root->clone();
    ASSERT_EQ(*(clonedRoot.get()), *(root.get()));
    ASSERT_NE(clonedRoot, root);
    ASSERT_EQ(clonedRoot->getParent().lock(), nullptr);
    ASSERT_EQ(*(clonedRoot->getChild("child1").lock()), *(root->getChild("child1").lock()));
    ASSERT_EQ(*(clonedRoot->getChild("child2").lock()), *(root->getChild("child2").lock()));

    ASSERT_NE(clonedRoot->getChild("child2").lock()->getChild("child21").lock(), 
                    root->getChild("child2").lock()->getChild("child21").lock());
    ASSERT_NE(clonedRoot->getChild("child2").lock(),
                    root->getChild("child2").lock()->getChild("child21").lock()->getParent().lock());
    ASSERT_EQ(clonedRoot->getChild("child2").lock(), 
              clonedRoot->getChild("child2").lock()->getChild("child22").lock()->getParent().lock());

}
// TEST(NodeTest, Traverse) {
//     auto root = std::make_unique<Node>();
//     auto child1 = std::make_unique<Node>();
//     auto child2 = std::make_unique<Node>();
//     auto grandchild1 = std::make_unique<Node>();

//     child1->addChild("grandchild1", std::move(grandchild1));
//     root->addChild("child1", std::move(child1));
//     root->addChild("child2", std::move(child2));

//     std::vector<Node*> visited;
//     root->traverse([&visited](Node& node) {
//         visited.push_back(&node);
//     });

//     // We should have visited child1, grandchild1, and child2
//     EXPECT_EQ(visited.size(), 3);
//     // order depends on map iteration but we expect insertion order here
//     EXPECT_EQ(visited[0], root->getChild("child1"));
//     EXPECT_EQ(visited[2], root->getChild("child2"));
// }
