#include "../../include/astrocore/nodes/shapenode.h"

using namespace Astrocore;

ShapeNode::ShapeNode()
{
    shapesToDraw = std::vector<Shape>();
    isDrawn = true;
}

ShapeNode::ShapeNode(Shape initialShape) : ShapeNode()
{
    this->shapesToDraw.push_back(initialShape);
}

void ShapeNode::Draw()
{

    Matrix transMat = GetWorldTransform().GetMatrix();
    for (auto shape : shapesToDraw)
    {
        if (shape.isFilled)
        {
            std::vector<Vector2> newPoints = shape.points;

            // Determine center point
            Vector2 center = {0, 0};
            for (int i = 0; i < newPoints.size(); i++)
            {
                newPoints.at(i) = Vector2Transform(newPoints.at(i), transMat);
                center = Vector2Add(center, newPoints.at(i));
            }
            center = {center.x / (float)newPoints.size(), center.y / (float)newPoints.size()};

            // Really cheap triangulation lol
            for (int i = 0; i < newPoints.size(); i++)
            {
                int first = i;
                int next = (i + 1) % newPoints.size();
                DrawTriangle(center, newPoints.at(next), newPoints.at(first), shape.color);
            }
        }
        else
        {
            for (int i = 0; i < shape.points.size() - 1; i++)
            {
                DrawLineEx(Vector2Transform(shape.points[i], transMat), Vector2Transform(shape.points[i + 1], transMat), shape.lineWidth, shape.color);
            }
            if (shape.isClosed)
            {
                DrawLineEx(Vector2Transform(shape.points[shape.points.size() - 1], transMat), Vector2Transform(shape.points[0], transMat), shape.lineWidth, shape.color);
            }
        }
    }
}