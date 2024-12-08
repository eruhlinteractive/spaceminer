#ifndef SCENETREE_H
#define SCENETREE_H

#include <vector>
#include <memory>
#include "../nodes/treenode.h"

namespace Astrocore
{
    class SceneTree
    {
        friend class Node;
        friend class Game;
        private:
        // The root of the entire tree
        std::unique_ptr<TreeNode> treeRoot;
        inline static bool created = false;    // Track if we've already created an instance

        // Track all nodes currently in the scene
        std::unique_ptr<std::vector<TreeNode*>> drawnNodesInScene = 
            std::unique_ptr<std::vector<TreeNode*>>(new std::vector<TreeNode*>());
        
        // The base node of the current scene 
        // NOTE: Using weak ptrs here because we don't want to explicitly own the object
        TreeNode* currentScene;

        std::weak_ptr<void> currentCamera;

    public:
        SceneTree();
        ~SceneTree(); 
        TreeNode* GetRoot();
        
        // Set's the current scene WITHOUT deleting the current scene
        void SetCurrentScene(TreeNode* newSceneRoot);
        // Set's the current scene, deleting the old scene
        void SwapCurrentScene(TreeNode* newSceneRoot);
        void Update(float deltaTime);
        void FixedUpdate(float deltaTime);
        void RegisterToTree(TreeNode* nodeToRegister);
        void DeRegisterToTree(TreeNode* nodeToDeRegister);
    };
}
#endif // !SCENETREE