#pragma once
#include <vector>
#include <raylib.h>
#include <unordered_map>
#include <iostream>
class EnvironmentObject
{
    public:
        EnvironmentObject(Vector2 Position, Vector2 Size) : m_Position(Position), m_Size(Size) {};
        virtual ~EnvironmentObject() = default;
        virtual void update() = 0;
        virtual void render() = 0;
    protected:
        Vector2 m_Position;
        Vector2 m_Size;
};
class EnvironmentObjectFactory // Singleton Factory
{
    public:
    enum EnvironmentObjectType
    {
        GROUND,
        WARP_PIPE,
        BRICK,
        QUESTION_BLOCK
    };
    private:
        EnvironmentObjectFactory() = default;
        ~EnvironmentObjectFactory() = default;
    public:
        static EnvironmentObjectFactory& GetEnvironmentFactory();
        EnvironmentObject* CreateEnvironmentObject(int Type, Vector2 Position);
};
class Ground : public EnvironmentObject // Singleton
{
    private:
        Texture2D m_Texture;
    private:
        Ground();
        ~Ground();
        void render() override;
        void update() override;
    public:
        static EnvironmentObject* GetGround();
};
class WarpPipe : public EnvironmentObject
{
    public:
    WarpPipe(Vector2 Position, Vector2 Size);
    ~WarpPipe();
    void render() override;
    void update() override;
};
class WarpPipeTextureFlyWeight // Singleton Flyweight
{
    private:
        Texture2D m_Texture;
    private:
        WarpPipeTextureFlyWeight();
        ~WarpPipeTextureFlyWeight();
    public:
        static WarpPipeTextureFlyWeight* GetWarpPipeTextureFlyweight();
        void render(Vector2 Position);
};
class Brick : public EnvironmentObject
{
    public:
    Brick(Vector2 Position, Vector2 Size);
    ~Brick();
    void render() override;
    void update() override;
};
class BrickTextureFlyWeight // Singleton Flyweight
{
    private:
        Texture2D m_Texture;
    private:
        BrickTextureFlyWeight();
        ~BrickTextureFlyWeight();
    public:
        static BrickTextureFlyWeight* GetBrickTextureFlyWeight();
        void render(Vector2 Position);
};