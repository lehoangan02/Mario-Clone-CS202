#pragma once
#include <vector>
#include <raylib.h>
#include <unordered_map>
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
    enum EnvironmentObjectType
    {
        WARP_PIPE,
        GROUND,
        BRICK,
        QUESTION_BLOCK
    };
    private:
        EnvironmentObjectFactory() = default;
        ~EnvironmentObjectFactory() = default;
    public:
        EnvironmentObjectFactory& GetEnvironmentFactory();
        EnvironmentObject& CreateEnvironmentObject(int Type);
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
        static EnvironmentObject& GetGround();
};
class WarpPipe : public EnvironmentObject
{
    public:
    WarpPipe();
    ~WarpPipe();
};
class WarpPipeTextureFlyWeight // Singleton Flyweight
{
    private:
        WarpPipeTextureFlyWeight();
        ~WarpPipeTextureFlyWeight();
    public:
        Texture2D& GetWarpPipeTexture();
        void render(Vector2 Position);
};
class Brick : public EnvironmentObject
{
    private:
    
    public:
    Brick();
    ~Brick();
};
class BrickTextureFlyWeight // Singleton Flyweight
{
    private:
        BrickTextureFlyWeight();
        ~BrickTextureFlyWeight();
    public:
        Texture2D& GetBrickTexture();
        void render(Vector2 Position);
};
class TextureFlyweightFactory // Singleton Factory
{
    private:
        TextureFlyweightFactory();
        ~TextureFlyweightFactory();
    public:
        Texture2D& GetTextureFlyweight();
        Texture2D& CreateTextureFlyweight(const char* TexturePath);
};