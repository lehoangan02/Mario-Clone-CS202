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
	Command* m_Command;
    std::vector<Enemy*> m_Enemies;
    std::vector<Item*> m_Items;
    std::vector<EnvironmentObject*> m_Environment;
    std::vector<EnvironmentObjectInteractive*> m_EnvironmentInteractive;
    std::vector<DrawableObject*> m_Drawables;
    Character* m_Player;
    Vector2 m_PlayerSpawn;
    Vector2 m_CameraPosition;
    Ground* m_Ground;
    const float m_PlayerOffset = 500;
    bool isPlayerFinished = false;
    Vector2 m_ScreenSize = {1200, 900};
    protected:
        Level();
        ~Level();
    public:
        void attachPlayer(Character* Player);
        virtual void load() = 0;
        virtual void update(float DeltaTime);
        virtual void render();
        void setOpeningScreenSize(int Width, int Height) { m_ScreenSize = Vector2{(float)Width, (float)Height}; };
    protected:
        void checkEnvironmentCollisions();
        void resolveEnvironmentCollisions();
        void resolveInteractiveEnvironmentCollisions();
        void applyBoundaries();
        bool isInHole();
        void resolveHoleCollisions();
        void setCommand(Command* command) { m_Command = command; };
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
        void load() override;
        void update(float DeltaTime) override;
        void render() override;
    public:
        static Level101* GetLevel101();
};
