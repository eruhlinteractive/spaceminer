#ifndef RENDERER_H
#define RENDERER_H

#ifndef RAYLIB_H
#include <raylib.h>
#endif // !RAYLIB_H

#include <memory>
#include "../../nodes/node.h"
#include "rendertarget.h"
#include <bitset>

namespace Astrocore
{
    /// Flags to determine how the render target should fit the bounds of the screen
    enum RenderScaleFlag
    {
        SCALE_STRETCH_FILL, // Stretches the image to fill both axies
        SCALE_FIT_WIDTH, // Fit the width
        SCALE_FIT_HEIGHT,// Fit the height
        SCALE_KEEP_ASPECT_FIT, // Scale to fit the smallest dimension, keeping the aspect (may introduce letterboxing)
        SCALE_KEEP_ASPECT_FILL // Scale to fit the smallest dimension, making sure to fill the screen
    };

    class Renderer
    {
        
        friend class Game;
        private:
            Vector2 targetRenderResolution = {0,0};
            RenderTexture2D finalRenderTexture;
            //float virtualScreenWidth = 1;   // Scaling factor of the finalRenderTarget to fit in the window
            // TODO: Add render bit flags for layers to use
            std::map<std::string, RenderTarget*> renderTargets;
            Rectangle srcRect;
            Rectangle destRect;
            RenderTarget* basicTarget;
            Color clearColor = WHITE;
            RenderScaleFlag scaleRenderFlag = SCALE_STRETCH_FILL;
            void UpdateRenderRects(float screenWidth, float screenHeight, RenderScaleFlag scaleMode);

        public:
            Renderer();
            ~Renderer();
            void SetClearColor(Color newColor);
            void SetFinalTargetDimensions(float width, float height);

            void AddRenderTarget(std::string name, RenderTarget* target);
            RenderTarget* GetRenderTarget(std::string name);
            void SetRenderStretchMode(RenderScaleFlag modeFlag);
            

        // Basic renderer
        // TODO: Add layer sorting, etc
            void Render(std::vector<TreeNode*>* nodesToDraw);
    };

}

#endif // !RENDERER