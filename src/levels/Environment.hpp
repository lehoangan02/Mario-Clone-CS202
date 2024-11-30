#pragma once
#include <vector>
#include <raylib.h>
#include <unordered_map>
#include <iostream>
#include "../animation/Animation.h"
#include "../Oberver/Observer.hpp"
#include "Flyweight.hpp"
class MapObject
{
    public:
        Vector2 m_Position;
        Vector2 m_Size;
    public:
        virtual void render() = 0;
        Vector2 getSize() { return m_Size; };
    protected:
        MapObject(Vector2 Position, Vector2 Size) : m_Position(Position), m_Size(Size) {};
        
};
class DrawableObject : public MapObject
{
    protected:
        DrawableObject(Vector2 Position) : MapObject(Position, Vector2{0, 0}) {};
        
    public:
        // virtual void render() = 0;
        virtual ~DrawableObject() = default;
};
class EnvironmentObject : public MapObject
{
    public:
        EnvironmentObject(Vector2 Position, Vector2 Size) : MapObject(Position, Size) {};
        virtual ~EnvironmentObject() = default;
        virtual void update() = 0;
        // virtual void render() = 0;
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
        MOUNTAIN,
        CASTLE
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
        WARP_PIPE, // 0
        WARP_PIPE_SHORT, // 1
        WARP_PIPE_TINY, // 2
        BRICK, // so on & so on
        HARD_BLOCK,
        BLUE_BRICK,
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
class Lift : public MapObject
{
    public:
    Lift(Vector2 Position);
    ~Lift();
    void render() override;
    void update(float DeltaTime);
    private:
    float m_Speed = 100;
};
class Ground : public MapObject // Singleton
{
    friend class Level;
    private:
        Texture2D m_Texture[2] = {LoadTexture("assets/textures/ground1x1.png"), LoadTexture("assets/textures/ground_blue1x1.png")};
        std::vector<std::pair<float, int>> m_Holes;
        Vector2 m_CameraPosition;
        int m_WorldType = 0;
    private:
        Ground();
        ~Ground();
        void update(Vector2 CameraPosition);
    public:
        void clearHoles() { m_Holes.clear(); };
        void render();
        static Ground* GetGround();
        void addHole(float x, unsigned int y); // y is how many bricks wide the hole is
        std::pair<float, unsigned int> getHole(unsigned int index) { return m_Holes[index]; };
        int getHoleCount() { return m_Holes.size(); };
        void setWorldType(int Type) { m_WorldType = Type; };
};
class WarpPipe : public EnvironmentObject
{
    public:
    WarpPipe(Vector2 Position);
    ~WarpPipe();
    void render() override;
    void update() override;
};

class Brick : public EnvironmentObject
{
    public:
    Brick(Vector2 Position);
    ~Brick();
    void render() override;
    void update() override;
};
class HardBlock : public EnvironmentObject
{
    public:
    HardBlock(Vector2 Position);
    ~HardBlock();
    void render() override;
    void update() override;
};
class BlueBrick : public EnvironmentObject
{
    public:
    BlueBrick(Vector2 Position);
    ~BlueBrick();
    void render() override;
    void update() override;
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
        float m_Speed = 120;
       
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
    Rectangle HittedTextureRect = {100, 0, 100, 100};
    private:
    Rectangle getCurrentTextureRect();
};
class Cloud : public DrawableObject
{
    public:
    Cloud(Vector2 Position);
    ~Cloud();
    void render() override;
};
class Castle : public DrawableObject
{
    private:
    Texture2D m_Texture = LoadTexture("assets/textures/castle.png");
    public:
    Castle(Vector2 Position);
    ~Castle();
    void render() override;
};
class Grass : public DrawableObject
{
    public:
    Grass(Vector2 Position);
    ~Grass();
    void render() override;
};
class Mountain : public DrawableObject
{
    public:
    Mountain(Vector2 Position);
    ~Mountain();
    void render() override;
};
enum EndPipeType
{
    TOP,
    SIDE
};
class EndPipeTop : public EnvironmentObject
{
    public:
    EndPipeTop(Vector2 Position);
    ~EndPipeTop();
    void render() override;
    void update() override;
};