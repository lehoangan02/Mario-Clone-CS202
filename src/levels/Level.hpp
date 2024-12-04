#pragma once
#include <vector>
#include "Environment.hpp"
#include "../characters/Character.h"
#include "AABBox.hpp"
#include "MapLoader.hpp"
class Enemy;
class Item;
enum LEVEL_RETURN_MESSAGE
{
    PAUSE,
    CONTINUE,
    RUNNING,
    HIDDEN,
    WIN,
    LOSE,
    QUIT
};

class Level : public Subject
{
    public:
        enum WorldType
        {
            OVERWORLD,
            UNDERGROUND
        };
    friend class MapLoader;
    protected:
    int m_LevelID;
    std::vector<Enemy*> m_Enemies;
    std::vector<Item*> m_Items;
    std::vector<EnvironmentObject*> m_Environment;
    std::vector<EnvironmentObjectInteractive*> m_EnvironmentInteractive;
    std::vector<DrawableObject*> m_Drawables;
    std::vector<Lift*> m_Lifts;
    std::vector<EndPipeTop*> m_EndPipes;
    Character* m_Player;
    Vector2 m_PlayerSpawn;
    Vector2 m_CameraPosition = {0, 0};
    Ground* m_Ground;
    int m_WorldType;
    const float m_PlayerOffset = 500;
    bool isPlayerFinished = false;
    Vector2 m_ScreenSize = {1200, 900};
    MapLoader* m_MapLoader;
    private:
        bool m_Paused = false;
    public:
        void attachPlayer(Character* Player);
        virtual unsigned int update(float DeltaTime);
        virtual void render();
        void pauseLevel();
        void continueLevel();
        LevelFactory::LevelType GetLevelType() { return (LevelFactory::LevelType)m_LevelID; };
    protected:
        void setOpeningScreenSize(int Width, int Height) { m_ScreenSize = Vector2{(float)Width, (float)Height}; };
        virtual void load() = 0;
        Level();
        ~Level();
        void checkEnvironmentCollisions();
        void resolveEnvironmentCollisions();
        void resolveInteractiveEnvironmentCollisions();
        void applyBoundaries();
        bool isInHole();
        void resolveHoleCollisions();
        unsigned int doPauseLogic();
};
class LevelFactory
{
    public:
        enum LevelType
        {
            LEVEL_101 = 0,
            HIDDEN_LEVEL_101,
            LEVEL_102,
            HIDDEN_LEVEL_102,
            HIDDEN_LEVEL_112,
            LEVEL_103,
            HIDDEN_LEVEL_103,
            LEVEL_TESTING,
            
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
    friend class LevelFactory;
    private:
        Level101();
        ~Level101();
        void load() override;
        unsigned int update(float DeltaTime) override;
        void render() override;
        static Level101* GetLevel101();
};
class HiddenLevel101 : public Level
{
    private:
        HiddenLevel101();
        ~HiddenLevel101();
        void load() override;
        unsigned int update(float DeltaTime) override;
        void render() override;
    public:
        static HiddenLevel101* GetHiddenLevel101();
};
class LevelTesting : public Level
{
    friend class LevelFactory;
    private:
        LevelTesting();
        ~LevelTesting();
        void load() override;
        unsigned int update(float DeltaTime) override;
        void render() override;
    public:
        static LevelTesting* GetLevelTesting();
};
class Level103 : public Level
{
    friend class LevelFactory;
    private:
        Level103();
        ~Level103();
        // void load() override;
        // unsigned int update(float DeltaTime) override;
        // void render() override;
        void load() override;
    public:
        static Level103* GetLevel103();
};
