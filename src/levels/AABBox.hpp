#pragma once
#include <vector>
#include <raylib.h>
#include <iostream>
class AABBox
{
    public:
        AABBox(Vector2 Position, Vector2 Size) : m_Position(Position), m_Size(Size) {};
        void setFixed(bool fixed) { m_Fixed = fixed; };
        Vector2 getPosition() { return m_Position; };
        Vector2 getSize() { return m_Size; };
    private:
        Vector2 m_Position;
        Vector2 m_Size;
        bool m_Fixed = false;
    friend void resolveCollisions(AABBox &AABBox1, AABBox &AABBox2);
    friend bool isColliding(const AABBox &AABBox1, const AABBox &AABBox2);
    friend bool isCollidingOnVertically(const AABBox &AABBox1, const AABBox &AABBox2);
    friend bool isCollidingOnTop(const AABBox &AABBox1, const AABBox &AABBox2);
    friend bool isCollidingOnBottom(const AABBox &AABBox1, const AABBox &AABBox2);
    friend bool isCollidingLeft(const AABBox &AABBox1, const AABBox &AABBox2);
    friend bool isCollidingHorizontally(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold);
    friend bool isCollidingOnVertically(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold);
    friend bool isCollidingHorizontallyRaw(const AABBox &AABBox1, const AABBox &AABBox2);
    friend bool isCollidingVerticallyRaw(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold);
    friend bool isCollidingHorizontallyRawLess(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold);
    // friend void resolveCollision(AABBox &AABBox1, AABBox &AABBox2, bool Fixed);
    friend bool isCollidingHorizontally(const AABBox &AABBox1, const AABBox &AABBox2);


};
void resolveCollisions(AABBox &AABBox1, AABBox &AABBox2);
// void resolveCollision(AABBox &AABBox1, AABBox &AABBox2, bool Fixed);
bool isColliding(const AABBox &AABBox1, const AABBox &AABBox2);
bool isCollidingOnVertically(const AABBox &AABBox1, const AABBox &AABBox2);
bool isCollidingVerticallyRaw(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold);
bool isCollidingHorizontallyRaw(const AABBox &AABBox1, const AABBox &AABBox2);
bool isCollidingOnTop(const AABBox &AABBox1, const AABBox &AABBox2);
bool isCollidingOnBottom(const AABBox &AABBox1, const AABBox &AABBox2);
bool isCollidingLeft(const AABBox &AABBox1, const AABBox &AABBox2);
bool isCollidingHorizontallyRaw(const AABBox &AABBox1, const AABBox &AABBox2);
bool isCollidingHorizontally(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold);
bool isCollidingOnVertically(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold);
bool isCollidingHorizontallyRawLess(const AABBox &AABBox1, const AABBox &AABBox2, const float &Threshold);
bool isCollidingHorizontally(const AABBox &AABBox1, const AABBox &AABBox2);
// Function to draw a bounding box
void DrawBoundingBox(Vector2 position, Vector2 size, Color color);