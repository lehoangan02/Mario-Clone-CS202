#pragma once
#include <vector>
#include <raylib.h>
#include <unordered_map>
#include <iostream>
class MapObject
{
    public:
        Vector2 m_Position;
        Vector2 m_Size;
    public:
        MapObject(Vector2 Position, Vector2 Size) : m_Position(Position), m_Size(Size) {};
        virtual void render();
};
class DrawableObject : public MapObject
{
    public:
        DrawableObject(Vector2 Position) : MapObject(Position, Vector2{0, 0}) {};
        virtual ~DrawableObject() = default;
        virtual void render() = 0;
};
class EnvironmentObject : public MapObject
{
    public:
        EnvironmentObject(Vector2 Position, Vector2 Size) : MapObject(Position, Size) {};
        virtual ~EnvironmentObject() = default;
        virtual void update() = 0;
        virtual void render() = 0;
        Vector2 getSize() { return m_Size; };
};
class DrawableObjectFactory
{
    public:
    enum DrawableObjectType
    {
        GRASS,
        CLOUD,
        MOUNTAIN
    };
    private:
        DrawableObjectFactory() = default;
        ~DrawableObjectFactory() = default;
    public:
        static DrawableObjectFactory& GetDrawableObjectFactory();
        DrawableObject* CreateDrawableObject(int Type, Vector2 Position);
};
class EnvironmentObjectFactory // Singleton Factory
{
    public:
    enum EnvironmentObjectType
    {
        WARP_PIPE,
        WARP_PIPE_SHORT,
        WARP_PIPE_TINY,
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
class Ground : public MapObject // Singleton
{
    friend class Level;
    private:
        Texture2D m_Texture;
        std::vector<std::pair<float, int>> m_Holes;
    private:
        Ground();
        ~Ground();
        void update();
    public:
        void render(Vector2 CameraPosition);
        static Ground* GetGround();
        void addHole(float x, unsigned int y); // y is how many bricks wide the hole is
        std::pair<float, unsigned int> getHole(unsigned int index) { return m_Holes[index]; };
        int getHoleCount() { return m_Holes.size(); };
};
class WarpPipe : public EnvironmentObject
{
    public:
    WarpPipe(Vector2 Position);
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
    Brick(Vector2 Position);
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
class Cloud : public DrawableObject
{
    public:
    Cloud(Vector2 Position);
    ~Cloud();
    void render() override;
};
class CloudTextureFlyWeight // Singleton Flyweight
{
    private:
        Texture2D m_Texture;
    private:
        CloudTextureFlyWeight();
        ~CloudTextureFlyWeight();
    public:
        static CloudTextureFlyWeight* GetCloudTextureFlyWeight();
        void render(Vector2 Position);
};