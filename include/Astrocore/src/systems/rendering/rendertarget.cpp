#include "../../../include/astrocore/systems/rendering/rendertarget.h"
using namespace Astrocore;

RenderTarget::RenderTarget(std::string name)
{
    this->name = name;
}

void RenderTarget::SetRenderTargetDimensions(float width, float height)
{
    if(IsRenderTextureValid(renderTarget))
    {
        UnloadRenderTexture(renderTarget);
    }
    // TODO: This should update the destination rect
    renderTarget = LoadRenderTexture(width, height);
}

void RenderTarget::SetSourceRect(Rectangle src)
{
   sourceRect = src;
}

void RenderTarget::SetDestRect(Rectangle dest)
{
    destRect = dest;
}

std::shared_ptr<Camera2D> RenderTarget::GetActiveCamera()
{
    return renderCamera;
}
Rectangle RenderTarget::GetDestRect()
{
    return destRect;
}

Rectangle RenderTarget::GetSourceRect()
{
    return sourceRect;
}

void RenderTarget::DrawToTarget(std::vector<TreeNode*>* nodesToDraw)
{
    if(renderCamera == nullptr)
    {
        DBG_WARN("No active camera was found for render target " + this->name + ". Creating a default one...");
        renderCamera = std::shared_ptr<Camera2D>(new Camera2D());
        renderCamera.get()->offset = {destRect.width/2.0f, destRect.height/2.0f};
        renderCamera.get()->zoom = 1.0f;
    }
   
    BeginTextureMode(renderTarget);
    BeginMode2D(*renderCamera);
    ClearBackground(BLANK);

    // Do drawing of each node
    for(int i = 0; i < nodesToDraw->size();i++)
    {
        TreeNode* node = nodesToDraw->at(i);
        if(node->IsDrawn())
        {
            node->Draw();
        }
    }
    
    EndMode2D();
    EndTextureMode();
}

void RenderTarget::SetActiveCamera(std::shared_ptr<Camera2D> cam)
{
    renderCamera = cam;
}

void RenderTarget::DrawToFinal()
{   
    DrawTexturePro(renderTarget.texture, sourceRect, destRect, {0, 0}, 0, WHITE);
}