#pragma once
#include <vector>
#include "Environment.hpp"
class Enemy;
class Player;
class Item;
class Level
{
    protected:
    int m_LevelID;
    std::vector<Enemy*> m_Enemies;
    std::vector<Item*> m_Items;
    std::vector<EnvironmentObject*> m_Environment;
    Player* m_Player;
    protected:
        Level();
        ~Level();
    public:
        virtual void load() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
    private:
        void checkEnvironmentCollisions();
        void resolveEnvironmentCollisions();
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
        void update();
        void render();
    public:
        static Level101* GetLevel101();
};
