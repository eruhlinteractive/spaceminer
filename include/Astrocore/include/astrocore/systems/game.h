#ifndef GAME_H
#define GAME_H
#include <string>
#include "scenetree.h"
#include "rendering/renderer.h"
#include "debug.h"

namespace Astrocore
{
    class Game
    {
    private:
        inline static std::unique_ptr<SceneTree> sceneTree = std::unique_ptr<SceneTree>(new SceneTree());
        static void* physicsSystem; // TODO
        inline static std::unique_ptr<Renderer> renderer = std::unique_ptr<Renderer>(new Renderer()); 
        
        
    public:
        void Run(); // The main game loop
        Game(std::string title, int windowWidth, int windowHeight);
        ~Game();
        static inline SceneTree* GetSceneTree() { return sceneTree.get();};
        static inline Renderer* GetRenderer() { return renderer.get();};
    };
}
#endif // !GAME