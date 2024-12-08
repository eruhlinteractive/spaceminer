#ifndef SHAPENODE_H
#define SHAPENODE_H

#include <vector>

#ifndef RAYLIB_H
#include <raylib.h>
#include <raymath.h>
#endif // !RAYLIB_H

#include <cmath>
#include "node.h"

namespace Astrocore
{
    struct Shape;
    // A node that draws geometric shapes
    class ShapeNode : public Node
    {
    private:
        std::vector<Shape> shapesToDraw;

    public:
        ShapeNode();
        ShapeNode(Shape initialShape);
        //~ShapeNode();
        void AddShape(Shape newShape);
        void Draw() override;

    };

struct Shape
{
    std::vector<Vector2> points;
    bool isFilled = false;
    Color color = RED;
    Vector2 center = {0,0};
    float rotationOffset = 0;
    float lineWidth = 1.0f;
    float isClosed = true;

    Shape()
    {
        points = std::vector<Vector2>();
    };

    Shape(Vector2 center, float rotOffset = 0)
    {
        this->center = center;
        rotationOffset = rotOffset;
    }

    Shape AsRect(float height, float width)
    {
        points.clear();
        points.push_back({height/2.0f, width/2.0f});
        points.push_back({-height/2.0f, width/2.0f});
        points.push_back({-height/2.0f, -width/2.0f});
        points.push_back({height/2.0f, -width/2.0f});
        return *this;
    }

    Shape AsCircle(float radius, int resolution)
    {
        float pointOffset = (2.0 * PI) / resolution;
        float currAngle = 0;
        points.clear();
        for(int i= 0; i < resolution; i++)
        {
            currAngle = i * pointOffset;
            points.push_back({cos(currAngle) * radius, sin(currAngle)* radius});
        }

        return *this;
    }

    Shape SetFilled(bool isFilled)
    {
        this->isFilled = isFilled;
        return *this;
    }
    Shape SetLineThickness(float newThick)
    {
        lineWidth = newThick;
        return *this;
    }

    // Note: Points should be in COUNTER CLOCKWISE order
    Shape FromPoints(std::vector<Vector2> newPoints)
    {
        this->points.clear();
        points = newPoints;
        return *this;
    }

    Shape SetColor(Color col)
    {
        this->color = col;
        return *this;
    }
};
}


#endif // !SHAPENODE