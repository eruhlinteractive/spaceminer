#ifndef TREENODE_H
#define TREENODE_H
#include "../component/signaler.h"

namespace Astrocore
{
    // An object that is able to be registered/interacted with in a tree
    class SceneTree; // Forward declaration
    class TreeNode : public Signaler, Observer
    {
    private:
        bool isInTree = false;
        
    protected:
        SceneTree* registeredTree = nullptr; // TODO: Make this a pointer to the scene tree
        bool isDrawn = false;
        int zIndex = 0;
    
    public:
        TreeNode(){};
        virtual void EnterTree(SceneTree* tree)
        {
            this->isInTree = true; 
            this->registeredTree = tree;
        };
        virtual void ExitTree()
        {
            isInTree = false;
        };

        virtual void Draw(){};
        void GetZIndex();
        bool IsDrawn() {return isDrawn;};
        bool IsInTree(){return isInTree;};

        virtual void Update(float deltaTime){};
        virtual void FixedUpdate(float deltaTime){};
    };
}

#endif // !TREENODE