#include "include/Astrocore/include/astrocore/systems/game.h"
#include "testscene.cpp"

using namespace Astrocore;

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    Game* myGame = new Game("Astrocore Dev", 1280, 720);
    myGame->GetRenderer()->SetFinalTargetDimensions(420, 270);
    myGame->GetRenderer()->SetRenderStretchMode(SCALE_KEEP_ASPECT_FIT);
    myGame->GetRenderer()->SetClearColor(BLACK);
    SetTargetFPS(60);
    std::shared_ptr<TestScene> sceneRoot = std::shared_ptr<TestScene>(new TestScene());
    myGame->GetSceneTree()->SetCurrentScene(sceneRoot.get());
    myGame->Run();
    delete myGame;
    myGame = nullptr;
    return 0;

}