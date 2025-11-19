#include <gtest/gtest.h>

#include <Scene.hpp>
#include <Node.hpp>

#include <memory>
#include <vector>

using namespace Perspective::scene;

TEST(SceneTest, InitializeDoesNotCrash) {}
    
TEST(SceneTest, AddAndRemoveNodes) {
    Scene scene;
    ASSERT_NE(scene.getRootId(), "");

    // Check adding a root-level node
    auto nodeA = Node::create();
    auto nodeA_id = scene.addNode("NodeA", nodeA);

    ASSERT_EQ(nodeA_id.has_value(), true);
    ASSERT_EQ(scene.getNode(nodeA_id.value()).has_value(), true);
    ASSERT_EQ(scene.getNode(nodeA_id.value()).value(), nodeA);

    // Check adding a child node
    auto nodeB = Node::create();
    auto nodeB_id = scene.addNode("NodeB", nodeB, nodeA_id);

    ASSERT_EQ(nodeB_id.has_value(), true);
    ASSERT_EQ(scene.getNode(nodeB_id.value()).has_value(), true);
    ASSERT_EQ(scene.getNode(nodeB_id.value()).value(), nodeB);
    ASSERT_EQ(nodeA->getChild("NodeB").lock(), nodeB);

    // Check that all children IDs are added when adding nodes
    auto nodeC = Node::create();
    auto nodeD = Node::create();
    nodeC->addChild("NodeD", nodeD);
    auto nodeC_id = scene.addNode("NodeC", nodeC);

    ASSERT_EQ(nodeC_id.has_value(), true);
    ASSERT_EQ(scene.getNode(nodeC_id.value()).has_value(), true);
    ASSERT_EQ(scene.getNode(nodeC_id.value()).value(), nodeC);
    auto childrenIds = scene.getChildrenIds(nodeC_id.value());
    ASSERT_TRUE(childrenIds.has_value());
    ASSERT_EQ(childrenIds->size(), 1);
    ASSERT_EQ(scene.getNode(childrenIds->at(0)).value(), nodeD);
    
    // Check adding nodes with invalid parent or duplicate names
    auto nodeCount = scene.getNodeCount();
    auto nodeE = Node::create();
    auto nodeF = Node::create();
    auto nodeE_id = scene.addNode("NodeE", nodeE, std::string("abcd-efgh-ijkl-mnop")); // non-existent parent
    
    ASSERT_EQ(nodeE_id.has_value(), false);
    ASSERT_EQ(scene.getNodeCount(), nodeCount); // node count should not change

    auto nodeF_id = scene.addNode("NodeB", nodeF, nodeA_id); // existing name under parent
    ASSERT_EQ(nodeF_id.has_value(), false);
    ASSERT_EQ(scene.getNodeCount(), nodeCount); // node count should not change

    // Check removing a node
    auto nodeDChildren = scene.getChildrenIds(nodeC_id.value());
    auto nodeD_id = (nodeDChildren && !nodeDChildren->empty())
    ? std::optional<std::string>(nodeDChildren->front())
    : std::nullopt;
    scene.removeNode(nodeC_id.value());
    
    ASSERT_EQ(scene.getNode(nodeC_id.value()).has_value(), false);
    ASSERT_EQ(scene.getNode(nodeD_id.value()).has_value(), false); // child should also be removed
    ASSERT_EQ(scene.getNodeCount(), nodeCount - 2); // node count should decrease by 2
}

TEST(SceneTest, TraverseVisitsAllNodes) {
    Scene scene;
    auto nodeA = Node::create();
    auto nodeB = Node::create();
    auto nodeC = Node::create();
    auto nodeD = Node::create();

    auto nodeA_id = scene.addNode("NodeA", nodeA);
    auto nodeB_id = scene.addNode("NodeB", nodeB, nodeA_id);
    auto nodeC_id = scene.addNode("NodeA", nodeC, nodeA_id);
    auto nodeD_id = scene.addNode("NodeD", nodeD);

    std::vector<std::shared_ptr<Node>> visitedNodes;
    scene.traverse([&visitedNodes](Node& node) {
        visitedNodes.push_back(node.shared_from_this());
    });

    ASSERT_EQ(visitedNodes.size(), 4);
    ASSERT_NE(std::find(visitedNodes.begin(), visitedNodes.end(), nodeA), visitedNodes.end());
    ASSERT_NE(std::find(visitedNodes.begin(), visitedNodes.end(), nodeB), visitedNodes.end());
    ASSERT_NE(std::find(visitedNodes.begin(), visitedNodes.end(), nodeC), visitedNodes.end());
    ASSERT_NE(std::find(visitedNodes.begin(), visitedNodes.end(), nodeD), visitedNodes.end());
}

