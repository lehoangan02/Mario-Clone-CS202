#pragma once
#include <vector>
#include "raylib.h"

enum TextureType
{
    WARP_PIPE,
    BRICK,
    HARD_BLOCK,
    QUESTION_BLOCK,
    CLOUD
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
class CloudTextureFlyWeight : public StaticFlyweight // Singleton Flyweight
{
    private:
        CloudTextureFlyWeight();
        ~CloudTextureFlyWeight();
    public:
        static CloudTextureFlyWeight* GetCloudTextureFlyWeight();
        void render(Vector2 Position);
};