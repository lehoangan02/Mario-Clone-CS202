#include "AABBox.hpp"
int Tollerance = 5;
void resolveCollisions(AABBox &AABBox1, AABBox &AABBox2)
{
    // std::cout << "Resolving collisions" << std::endl;
    if (AABBox1.m_Fixed && AABBox2.m_Fixed)
    {
        return;
    }
    if (isColliding(AABBox1, AABBox2))
    {
        // std::cout << "Colliding" << std::endl;
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        // std::cout << "Delta: " << Delta.x << ", " << Delta.y << std::endl;
        if (fabs(Intersect.x) < fabs(Intersect.y))
        {
            if (AABBox2.m_Fixed)
            {
                if (Delta.x > 0)
                {
                    AABBox1.m_Position.x = AABBox2.m_Position.x - AABBox1.m_Size.x;

                }
                else
                {
                    AABBox1.m_Position.x = AABBox2.m_Position.x + AABBox2.m_Size.x;
                }
            }
            else
            {
                if (Delta.x > 0)
                {
                    AABBox2.m_Position.x = AABBox1.m_Position.x - AABBox2.m_Size.x;
                }
                else
                {
                    AABBox2.m_Position.x = AABBox1.m_Position.x + AABBox1.m_Size.x;
                }
            }
        }
        else
        {
            if (AABBox2.m_Fixed)
            {
                if (Delta.y > 0)
                {
                    AABBox1.m_Position.y = AABBox2.m_Position.y - AABBox1.m_Size.y;
                }
                else
                {
                    AABBox1.m_Position.y = AABBox2.m_Position.y + AABBox2.m_Size.y;
                }
            }
            else
            {
                if (Delta.y > 0)
                {
                    AABBox2.m_Position.y = AABBox1.m_Position.y - AABBox2.m_Size.y;
                }
                else
                {
                    AABBox2.m_Position.y = AABBox1.m_Position.y + AABBox1.m_Size.y;
                }
            }
        }
        
    }
    else 
    {
        // std::cout << "Not colliding" << std::endl;
    }
}
// void resolveCollisions(AABBox &AABBox1, AABBox& AABBox2, bool Fixed)
// {

// }
bool isColliding(const AABBox &AABBox1, const AABBox &AABBox2)
{
    Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
    Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
    Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
    Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
    if (Intersect.x < 0 && Intersect.y < 0)
    {
        return true;
    }
    return false;
}
bool isCollidingOnVertically(const AABBox &AABBox1, const AABBox &AABBox2)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        if (fabs(Intersect.y) < fabs(Intersect.x))
        {
            // std::cout << "Colling on vertically" << std::endl;
            return true;
        }
    }
    return false;
}
bool isCollidingOnVertically(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        if (fabs(Intersect.y) < fabs(Intersect.x) && fabs(Intersect.y) > Threshold)
        {
            // std::cout << "IntersectY: " << Intersect.y << std::endl;
            // std::cout << "Colling on vertically" << std::endl;
            return true;
        }
    }
    return false;

}
bool isCollidingOnTop(const AABBox &AABBox1, const AABBox &AABBox2)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        if (fabs(Intersect.y) < fabs(Intersect.x) && Delta.y > 0)
        {
            // std::cout << "Colling on top" << std::endl;
            return true;
        }
    }
    return false;
}
bool isCollidingOnBottom(const AABBox &AABBox1, const AABBox &AABBox2)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        if (fabs(Intersect.y) < fabs(Intersect.x) && Delta.y < 0)
        {
            // std::cout << "Colling on bottom" << std::endl;
            return true;
        }
    }
    return false;
}
bool isCollidingHorizontallyRaw(const AABBox &AABBox1, const AABBox &AABBox2)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        if (fabs(Intersect.x) != 0)
        {
            // std::cout << "Colling on horizontally" << std::endl;
            return true;
        }
    }
    return false;
}
bool isCollidingLeft(const AABBox &AABBox1, const AABBox &AABBox2)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        if (fabs(Intersect.x) < fabs(Intersect.y) && Delta.x > 0)
        {
            // std::cout << "Colling on left" << std::endl;
            return true;
        }
    }
    return false;
}
bool isCollidingHorizontally(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        if (fabs(Intersect.x) < fabs(Intersect.y) && fabs(Intersect.x) > Threshold)
        {
            // std::cout << "Colling on horizontally" << std::endl;
            return true;
        }
    }
    return false;
}
bool isCollidingVerticallyRaw(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        if (fabs(Intersect.y) > Threshold)
        {
            // std::cout << "Colling on vertically" << std::endl;
            return true;
        }
    }
    return false;
}
bool isCollidingHorizontallyRawLess(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};

        if (fabs(Intersect.x) < Threshold && fabs(Intersect.x) != 0)
        {
            // std::cout << "interesectX: " << Intersect.x << std::endl;
            return true;
        }
        // std::cout << "interesectX: " << Intersect.x << std::endl;
    }
    return false;
}
bool isCollidingHorizontally(const AABBox &AABBox1, const AABBox &AABBox2)
{
    if (isColliding(AABBox1, AABBox2))
    {
        Vector2 Center1 = {AABBox1.m_Position.x + AABBox1.m_Size.x / 2, AABBox1.m_Position.y + AABBox1.m_Size.y / 2};
        Vector2 Center2 = {AABBox2.m_Position.x + AABBox2.m_Size.x / 2, AABBox2.m_Position.y + AABBox2.m_Size.y / 2};
        Vector2 Delta = {Center2.x - Center1.x, Center2.y - Center1.y};
        Vector2 Intersect = {fabs(Delta.x) - (AABBox1.m_Size.x / 2 + AABBox2.m_Size.x / 2), fabs(Delta.y) - (AABBox1.m_Size.y / 2 + AABBox2.m_Size.y / 2)};
        if (fabs(Intersect.x) < fabs(Intersect.y))
        {
            // std::cout << "Colling on horizontally" << std::endl;
            return true;
        }
    }
    return false;
}
void DrawBoundingBox(Vector2 position, Vector2 size, Color color) {
    // Calculate the four corners of the bounding box
    Vector2 topLeft = position;
    Vector2 topRight = { position.x + size.x, position.y };
    Vector2 bottomLeft = { position.x, position.y + size.y };
    Vector2 bottomRight = { position.x + size.x, position.y + size.y };

    // Draw the four edges of the bounding box
    DrawLineEx(topLeft, topRight, 2.0f, color); // Top edge
    DrawLineEx(topRight, bottomRight, 2.0f, color); // Right edge
    DrawLineEx(bottomRight, bottomLeft, 2.0f, color); // Bottom edge
    DrawLineEx(bottomLeft, topLeft, 2.0f, color); // Left edge
}