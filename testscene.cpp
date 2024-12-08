#include "include/Astrocore/include/astrocore/nodes/shapenode.h"
#include "include/Astrocore/include/astrocore/systems/resources/resourcemanager.h"
#include "include/Astrocore/include/astrocore/nodes/spritenode.h"

using namespace Astrocore;
class TestScene : public Node
{
    ShapeNode myShape = ShapeNode(Shape().AsRect(22,22).SetLineThickness(2).SetColor(RED));
    SpriteNode testSpriteNode = SpriteNode("resources/link.png");
    //ShapeNode outline = ShapeNode(Shape().AsRect(420, 270).SetLineThickness(2).SetColor(BLUE));
public:
    TestScene()
    {
        isDrawn = true;
        name = "Test Scene";   
    }
    void OnTreeEnter() override
    {
        testSpriteNode.SetSpriteCenterOffset({-9,-11});
        AddChild(&myShape);
        AddChild(&testSpriteNode);
        //AddChild(&outline);
    }

    void Update(float deltaTime)
    {
        //myShape.GetTransform()->RotateDegrees(20 * deltaTime);
        testSpriteNode.GetTransform()->Translate({-20*deltaTime,0});
    }
};