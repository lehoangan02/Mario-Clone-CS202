#pragma once
#include <vector>
#include <raylib.h>
#include <unordered_map>
#include <iostream>
#include "../animation/Animation.h"
#include "../Oberver/Observer.hpp"
class MapObject
{
    public:
        Vector2 m_Position;
        Vector2 m_Size;
    public:
        MapObject(Vector2 Position, Vector2 Size) : m_Position(Position), m_Size(Size) {};
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
class EnvironmentObjectInteractive : public EnvironmentObject, public Observer
{
    public:
        EnvironmentObjectInteractive(Vector2 Position, Vector2 Size) : EnvironmentObject(Position, Size) {};
        virtual ~EnvironmentObjectInteractive() = default;
    protected:
        void move(Vector2 Position);
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
    };
    private:
        EnvironmentObjectFactory() = default;
        ~EnvironmentObjectFactory() = default;
    public:
        static EnvironmentObjectFactory& GetEnvironmentFactory();
        EnvironmentObject* CreateEnvironmentObject(int Type, Vector2 Position);
};
class EnvironmentInteractiveObjectFactory // Singleton Factory
{
    public:
    enum EnvironmentInteractiveObjectType
    {
        QUESTION_BLOCK
    };
    private:
        EnvironmentInteractiveObjectFactory() = default;
        ~EnvironmentInteractiveObjectFactory() = default;
    public:
        static EnvironmentInteractiveObjectFactory& GetEnvironmentInteractiveFactory();
        EnvironmentObjectInteractive* CreateEnvironmentInteractiveObject(int Type, Vector2 Position);
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
class QuestionBlock : public EnvironmentObjectInteractive
{
    class HitAnimationCommander
    {
        private:
        bool m_HitTop = false;
        bool m_Finished = false;
        float m_MoveUpDistance = 0;
        float m_TopPosition = 0;
        float m_BottomPosition = 0;
        float m_Speed = 70;
        public:
        HitAnimationCommander(float MoveUpDistance, float BottomPosition);
        ~HitAnimationCommander();
        Vector2 giveMovementCommand(Vector2 CurrentPosition);
    };
    public:
    QuestionBlock(Vector2 Position);
    ~QuestionBlock();
    void render() override;
    void update() override;
    void onNotify() override;
    private:
    bool m_IsHit = false;
    Animation m_IdleAnimation;
    HitAnimationCommander m_HitAnimation;
    Rectangle getCurrentTextureRect();
};
class QuestionBlockTextureFlyWeight // Singleton Flyweight
{
    friend class QuestionBlock;
    private:
        Texture2D m_Texture;
    private:
        QuestionBlockTextureFlyWeight();
        ~QuestionBlockTextureFlyWeight();
    public:
        static QuestionBlockTextureFlyWeight* GetQuestionBlockTextureFlyWeight();
        void render(Vector2 Position, Rectangle TextureRect);
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