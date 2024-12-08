#ifndef __SPRITENODE_H__
#define __SPRITENODE_H__

#include "node.h"
#include <raymath.h>

namespace Astrocore
{
    class SpriteNode : public Node
    {
    private:
        /// @brief The offset of the sprite relative to the center
        Vector2 spriteCenterOffset = {0.0f, 0.0f};

        /// @brief The sprite texture to use for this node
        std::shared_ptr<Texture2D> spriteTexture;

    public:
        SpriteNode();
        SpriteNode(std::string spritePath);

        /// @brief Sets the offset of the drawn sprite relative to the transform
        /// @param offset The offset to apply
        void SetSpriteCenterOffset(Vector2 offset);

        /// @brief Gets the offset of the drawn sprite relative to the transform
        /// @return the  offset of the drawn sprite relative to the transform
        Vector2 GetSpriteCenterOffset();

        void SetSpritePath(std::string spritePath);
        void Draw() override;
    };
}
#endif // __SPRITENODE_H__