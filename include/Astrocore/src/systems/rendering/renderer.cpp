#include "../../../include/astrocore/systems/rendering/renderer.h"

using namespace Astrocore;

Renderer::Renderer()
{
    //SetFinalTargetDimensions(GetScreenWidth(), GetScreenHeight());
    renderTargets = std::map<std::string, RenderTarget*>();

    // Create and add basic rendering target with a cam
    basicTarget = new RenderTarget("basic");
    renderTargets.emplace("basic", basicTarget);
}


void Renderer::UpdateRenderRects(float screenWidth, float screenHeight, RenderScaleFlag scaleMode)
{
    float centerRenderOffsetX = 0;
    float centerRenderOffsetY = 0;
    switch (scaleMode)
    {
        case SCALE_STRETCH_FILL:
        {
            srcRect = {0, 0, targetRenderResolution.x, targetRenderResolution.y};
            destRect = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
            return;
        }
           
        case SCALE_FIT_WIDTH:
        {
            float widthFillPercent = (float)GetScreenWidth()/ targetRenderResolution.x;
            float newHeight = (float)targetRenderResolution.y * (widthFillPercent);
           
            // Calculate offset to keep the rendered view centered
            centerRenderOffsetY = ((float)GetScreenHeight()-newHeight)/2.0;
            srcRect = {0, 0, targetRenderResolution.x, targetRenderResolution.y};
            destRect = {0, centerRenderOffsetY, (float)GetScreenWidth(), newHeight};
            return;
        }
        case SCALE_FIT_HEIGHT:
        {
            float heightFillPercent = (float)GetScreenHeight()/ targetRenderResolution.y;
            float newWidth = (float)targetRenderResolution.x * (heightFillPercent);
           
            // Calculate offset to keep the rendered view centered
            centerRenderOffsetX = ((float)GetScreenWidth()-newWidth)/2.0;
            srcRect = {0, 0, targetRenderResolution.x, targetRenderResolution.y};
            destRect = {centerRenderOffsetX, 0, newWidth, (float)GetScreenHeight()};
            return;
        }

        case SCALE_KEEP_ASPECT_FIT:
        case SCALE_KEEP_ASPECT_FILL:
        {
            // Determine which dimension needs to be scaled and re-call accordingly
            float heightFillPercent = (float)GetScreenHeight()/ targetRenderResolution.y;
            float widthFillPercent = (float)GetScreenWidth()/ targetRenderResolution.x;

            RenderScaleFlag flagToUse;
            if(scaleMode == SCALE_KEEP_ASPECT_FIT)
            {
                flagToUse = heightFillPercent >= widthFillPercent ? SCALE_FIT_WIDTH : SCALE_FIT_HEIGHT;
            }
            else
            {
                flagToUse = heightFillPercent >= widthFillPercent ? SCALE_FIT_HEIGHT: SCALE_FIT_WIDTH;
            }
            
            this->UpdateRenderRects((float)GetScreenWidth(), (float)GetScreenHeight(), flagToUse);
            return;
        }
    }
}

   

void Renderer::SetFinalTargetDimensions(float width, float height)
{
    // track the initial dimensions to maintain the 
    Vector2 initialDimensions = targetRenderResolution;

    if(IsRenderTextureValid(finalRenderTexture))
    {
        UnloadRenderTexture(finalRenderTexture);
    }

    targetRenderResolution = {width, height};

    this->finalRenderTexture = LoadRenderTexture(width, height);
    SetTextureWrap(finalRenderTexture.texture, TEXTURE_WRAP_MIRROR_CLAMP);


    if(basicTarget != nullptr)
    {
        basicTarget->SetRenderTargetDimensions(width, height);
        basicTarget->SetDestRect({0,0,width, height});
        basicTarget->SetSourceRect({0,0,width, height});
    }

    UpdateRenderRects(GetScreenWidth(), GetScreenHeight(), scaleRenderFlag);
    
}

void Renderer::AddRenderTarget(std::string name, RenderTarget* target)
{
    renderTargets.insert({name, target});
}

RenderTarget* Renderer::GetRenderTarget(std::string name)
{
    return renderTargets.at(name);
}

Renderer::~Renderer()
{
    if(IsRenderTextureValid(finalRenderTexture))
    {
        UnloadRenderTexture(finalRenderTexture);
    }
    if(basicTarget != nullptr)
    {
        delete basicTarget;
        basicTarget = nullptr;
    }
}

void Renderer::SetClearColor(Color newColor)
{
    clearColor = newColor;        
}


void Renderer::SetRenderStretchMode(RenderScaleFlag modeFlag)
{
    scaleRenderFlag = modeFlag;
}


void Renderer::Render(std::vector<TreeNode*>* nodesToDraw)
{
    // Recalculate the render sizes
    if(IsWindowResized())
    {
        UpdateRenderRects(GetScreenWidth(), GetScreenHeight(), scaleRenderFlag);
    }

    BeginDrawing();
    ClearBackground(clearColor);
    // Render each of the targets
    std::map<std::string, RenderTarget*>::iterator it;

    for(it = renderTargets.begin(); it != renderTargets.end(); it++)
    {
        it->second->DrawToTarget(nodesToDraw);
    }

    // Render each of the targets to the final render texture
    BeginTextureMode(finalRenderTexture);
    ClearBackground(clearColor);
    for(it = renderTargets.begin(); it != renderTargets.end(); it++)
    {
        it->second->DrawToFinal();
    }
    EndTextureMode(); // finalRenderTarget

    // Render the final texture to the screen
    DrawTexturePro(finalRenderTexture.texture, srcRect, destRect, {0,0}, 0, WHITE);
    EndDrawing();
}