#ifndef RENDERTARGET_H
#define RENDERTARGET_H
#include <memory>
#include "../../component/transform2D.h"
#include <vector>
#include "../../nodes/treenode.h"

#include "../debug.h"

#ifndef RAYLIB_H
#include <raylib.h>
#endif // !RAYLIB_H

// Represents a single render target for a camera
namespace Astrocore
{

    class RenderTarget
    {
        private:
            std::string name;
            RenderTexture2D renderTarget;
            std::shared_ptr<Camera2D> renderCamera;
            Rectangle sourceRect;
            Rectangle destRect; // TODO: Should this be in screen coordinates

        public:
            RenderTarget(std::string name);
            void SetRenderTargetDimensions(float width, float height);  // Set the resolution of the target texture
            void SetSourceRect(Rectangle srcRect);    // Sets the screen-space size and pos of rendered image
            void SetDestRect(Rectangle dest);


            Rectangle GetSourceRect();
            Rectangle GetDestRect();

           
            void DrawToTarget(std::vector<TreeNode*>* nodesToDraw);
            void SetActiveCamera(std::shared_ptr<Camera2D> cam);
            std::shared_ptr<Camera2D> GetActiveCamera();

            void DrawToFinal();
    };
}

#endif // !RENDERTARGET