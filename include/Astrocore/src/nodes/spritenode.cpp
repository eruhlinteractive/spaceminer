#include "../../include/astrocore/nodes/spritenode.h"
#include "../../include/astrocore/systems/resources/resourcemanager.h"

using namespace Astrocore;

SpriteNode::SpriteNode() : Node()
{
    isDrawn = true;
    name = "SpriteNode" + std::to_string(GetNodeID());
}

SpriteNode::SpriteNode(std::string spritePath) : SpriteNode()
{
    spriteTexture = ResourceManager::instance()->GetTextureResource(spritePath);
}

void SpriteNode::SetSpritePath(std::string spritePath)
{
    spriteTexture = ResourceManager::instance()->GetTextureResource(spritePath);
}


void SpriteNode::SetSpriteCenterOffset(Vector2 offset)
{
    spriteCenterOffset = offset;
}


Vector2 SpriteNode::GetSpriteCenterOffset()
{  
    return spriteCenterOffset;
}


void SpriteNode::Draw()
{
    Transform2D transform = GetTransform();
    Vector2 transformedOffset = Vector2Transform(spriteCenterOffset, transform.GetMatrix());
    DrawTextureEx(*spriteTexture.get(), transform.GetPosition() + transformedOffset, transform.GetRotationDegrees(), Vector2Length(transform.GetScale()), WHITE );
}