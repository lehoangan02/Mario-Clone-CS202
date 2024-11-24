#pragma once
#include <vector>
#include "Environment.hpp"
#include "../characters/Character.h"
#include "AABBox.hpp"
class Enemy;
class Item;
class Level
{
    protected:
    int m_LevelID;
    std::vector<Enemy*> m_Enemies;
    std::vector<Item*> m_Items;
    std::vector<EnvironmentObject*> m_Environment;
    Character* m_Player;
    Vector2 m_PlayerSpawn;
    Vector2 m_CameraPosition;
    Ground* m_Ground;
    const float m_PlayerOffset = 500;
    bool isPlayerFinished = false;
    protected:
        Level();
        ~Level();
    public:
        void attachPlayer(Character* Player);
        virtual void load() = 0;
        virtual void update(float DeltaTime);
        virtual void render();
    protected:
        void checkEnvironmentCollisions();
        void resolveEnvironmentCollisions();
        void applyBoundaries();
        bool isInHole();
        void resolveHoleCollisions();
};
class LevelFactory
{
    public:
        enum LevelType
        {
            LEVEL_101 = 0
        };
    private:
        LevelFactory() = default;
        ~LevelFactory() = default;
    public:
        static LevelFactory& GetLevelFactory();
        Level* CreateLevel(LevelType Type);
};
class Level101 : public Level
{
    private:
        Level101();
        ~Level101();
        void load();
        void update(float DeltaTime);
        void render();
    public:
        static Level101* GetLevel101();
};
