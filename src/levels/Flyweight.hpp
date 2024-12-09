#pragma once
#include <vector>
#include "raylib.h"

enum TextureType
{
    WARP_PIPE,
    BRICK,
    HARD_BLOCK,
    QUESTION_BLOCK,
    CLOUD,
    BLUE_BRICK,
    LIFT,
    GRASS,
    MOUNTAIN,
    END_PIPE,
    EMPTY_QUESTION_BLOCK
};
class Flyweight
{
    protected:
        Texture2D m_Texture;
};
class StaticFlyweight : public Flyweight
{
    public:
        virtual void render(Vector2 Position) = 0;
};
class AniamtedFlyweight : public Flyweight
{
    public:
        virtual void render(Vector2 Position, Rectangle TextureRect) = 0;
        virtual Texture2D &getTexture() { return m_Texture; };
};
class StaticFlyweightFactory
{
    private:    
        StaticFlyweightFactory() = default;
        ~StaticFlyweightFactory() = default;
    public:
        StaticFlyweight* getFlyweight(int Type);
        static StaticFlyweightFactory* GetStaticFlyweightFactory();
};
class AnimatedFlyweightFactory
{
    private:
        AnimatedFlyweightFactory() = default;
        ~AnimatedFlyweightFactory() = default;
    public:
        AniamtedFlyweight* getFlyweight(int Type);
        static AnimatedFlyweightFactory* GetAnimatedFlyweightFactory();
};
class WarpPipeTextureFlyWeight : public StaticFlyweight// Singleton Flyweight
{
    private:
        WarpPipeTextureFlyWeight();
        ~WarpPipeTextureFlyWeight();
    public:
        static WarpPipeTextureFlyWeight* GetWarpPipeTextureFlyweight();
        void render(Vector2 Position);
};
class BrickTextureFlyWeight : public StaticFlyweight // Singleton Flyweight
{
    private:
        BrickTextureFlyWeight();
        ~BrickTextureFlyWeight();
    public:
        static BrickTextureFlyWeight* GetBrickTextureFlyWeight();
        void render(Vector2 Position);
};
class HardBlockTextureFlyWeight : public StaticFlyweight // Singleton Flyweight
{
    private:
        HardBlockTextureFlyWeight();
        ~HardBlockTextureFlyWeight();
    public:
        static HardBlockTextureFlyWeight* GetHardBlockTextureFlyWeight();
        void render(Vector2 Position);
};
class BlueBrickTextureFlyWeight : public StaticFlyweight // Singleton Flyweight
{
    private:
        BlueBrickTextureFlyWeight();
        ~BlueBrickTextureFlyWeight();
    public:
        static BlueBrickTextureFlyWeight* GetBlueBrickTextureFlyWeight();
        void render(Vector2 Position);
};
class LiftTextureFlyWeight : public StaticFlyweight // Singleton Flyweight
{
    private:
        LiftTextureFlyWeight();
        ~LiftTextureFlyWeight();
    public:
        static LiftTextureFlyWeight* GetLiftTextureFlyWeight();
        void render(Vector2 Position);
};
class QuestionBlockTextureFlyWeight : public AniamtedFlyweight // Singleton Flyweight
{
    friend class QuestionBlock;
    private:
        QuestionBlockTextureFlyWeight();
        ~QuestionBlockTextureFlyWeight();
    public:
        static QuestionBlockTextureFlyWeight* GetQuestionBlockTextureFlyWeight();
        void render(Vector2 Position, Rectangle TextureRect);
};
class EmptyQuestionBlockTextureFlyweight : public StaticFlyweight // Singleton Flyweight
{
    private:
        EmptyQuestionBlockTextureFlyweight();
        ~EmptyQuestionBlockTextureFlyweight();
    public:
        static EmptyQuestionBlockTextureFlyweight* GetEmptyQuestionBlockTextureFlyweight();
        void render(Vector2 Position);
};
class CloudTextureFlyWeight : public StaticFlyweight // Singleton Flyweight
{
    private:
        CloudTextureFlyWeight();
        ~CloudTextureFlyWeight();
    public:
        static CloudTextureFlyWeight* GetCloudTextureFlyWeight();
        void render(Vector2 Position);
};
class GrassTextureFlyWeight : public StaticFlyweight // Singleton Flyweight
{
    private:
        GrassTextureFlyWeight();
        ~GrassTextureFlyWeight();
    public:
        static GrassTextureFlyWeight* GetGrassTextureFlyWeight();
        void render(Vector2 Position);
};
class MountainTextureFlyWeight : public StaticFlyweight // Singleton Flyweight
{
    private:
        MountainTextureFlyWeight();
        ~MountainTextureFlyWeight();
    public:
        static MountainTextureFlyWeight* GetMountainTextureFlyWeight();
        void render(Vector2 Position);
};
class EndPipeTopTextureFlyWeight : public StaticFlyweight // Singleton Flyweight
{
    private:
        EndPipeTopTextureFlyWeight();
        ~EndPipeTopTextureFlyWeight();
    public:
        static EndPipeTopTextureFlyWeight* GetEndPipeTextureFlyWeight();
        void render(Vector2 Position);
};