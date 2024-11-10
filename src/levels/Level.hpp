#pragma once
#include <vector>
#include "Environment.hpp"
class Enemy;
class Player;
class Item;
class Level
{
    private:
    int m_LevelID;
    std::vector<Enemy*> m_Enemies;
    std::vector<Item*> m_Items;
    Player* m_Player;
    public:
        Level();
        ~Level();
        void load();
        void update();
        void render();
    private:
        void checkEnvironmentCollisions();
        void resolveEnvironmentCollisions();
};