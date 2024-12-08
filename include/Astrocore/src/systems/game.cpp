#include "../../include/astrocore/systems/game.h"
using namespace Astrocore;

Game::Game(std::string title, int windowWidth, int windowHeight)
{
    Debug::init();
    InitWindow(windowWidth, windowHeight, title.c_str());
    renderer->SetFinalTargetDimensions(windowWidth, windowHeight);
}

void Game::Run()
{
    while(!WindowShouldClose())
	{
        // Update
        sceneTree->GetRoot()->Update(GetFrameTime());
        // TODO: Physics Update
       renderer->Render(sceneTree->drawnNodesInScene.get());
    }


    renderer.reset();
    renderer = nullptr;
    // Cleanup
    CloseWindow();
}

Game::~Game()
{
    sceneTree.reset();
    sceneTree = nullptr;
}