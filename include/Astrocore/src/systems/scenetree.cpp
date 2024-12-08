#include "../../include/astrocore/systems/scenetree.h"
using namespace Astrocore;

SceneTree::SceneTree()
{
    SceneTree::created = true;
    treeRoot = std::unique_ptr<TreeNode>(new TreeNode());
}

SceneTree::~SceneTree()
{
    treeRoot.reset();
}

TreeNode* SceneTree::GetRoot()
{
    return currentScene;
}

void SceneTree::SetCurrentScene(TreeNode* newSceneRoot)
{
    this->currentScene = newSceneRoot;
    RegisterToTree(newSceneRoot);
}

void SceneTree::RegisterToTree(TreeNode* nodeToRegister)
{
    nodeToRegister->EnterTree(this);
    drawnNodesInScene->push_back(nodeToRegister);
}

void SceneTree::DeRegisterToTree(TreeNode* nodeToDeRegister)
{
    //drawnNodesInScene->erase();
    // TODO: Find in tree and push 
}