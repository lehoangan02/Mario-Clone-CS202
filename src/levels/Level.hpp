#pragma once
#include <vector>
#include "Environment.hpp"
#include "../characters/Character.h"
#include "AABBox.hpp"
#include "MapLoader.hpp"
#include "../Item/Item.h"
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
    class EndPipeHandler
    {
        private:
        std::vector<EndPipe*> m_EndPipes;
        Character* m_Player;
        bool inPipe = false;
        public:
        EndPipeHandler() = default;
        ~EndPipeHandler() = default;
        void addEndPipe(EndPipe* Pipe);
        void attachPlayer(Character* Player);
        bool update();
    };
    class Background
    {
        private:

        bool m_Overworld = true;

        Texture2D m_TextureLayer1;
        Texture2D m_TextureLayer2;
        Texture2D m_TextureLayer3;
        Texture2D m_TextureLayer4;
        Texture2D m_TextureLayer5;
        Texture2D m_TextureLayer6;
        Texture2D m_TextureLayer7;

        Texture2D m_TextureLayer8;
        Texture2D m_TextureLayer9;
        Texture2D m_TextureLayer10;
        Texture2D m_TextureLayer11;
        Texture2D m_TextureLayer12;
        Texture2D m_TextureLayer13;
        Texture2D m_TextureLayer14;

        Vector2 m_PreviousCameraPosition = {0, 0};


        Vector2 m_Layer1Position = {-00, -900};
        Vector2 m_Layer2Position = {-00, -1050};
        Vector2 m_Layer3Position = {-00, -900};
        Vector2 m_Layer4Position = {-00, -900};
        Vector2 m_Layer5Position = {-00, 0};
        Vector2 m_Layer6Position = {-00, 0};
        Vector2 m_Layer7Position = {-00, 0};

        Vector2 m_Layer8Position = {-00, -4110};
        Vector2 m_Layer9Position = {-00, -4110};
        Vector2 m_Layer10Position = {-00, -4110};
        Vector2 m_Layer11Position = {-00, -4110};
        Vector2 m_Layer12Position = {-00, -4110};
        Vector2 m_Layer13Position = {-00, -4110};
        Vector2 m_Layer14Position = {-00, -4110};
        public:
        Background();
        void update(Vector2 CameraPosition, bool Overworld);
        void render();
    };
    public:
        enum WorldType
        {
            OVERWORLD,
            UNDERGROUND
        };
    friend class MapLoader;
    // private:
        FlagPole m_FlagPole = FlagPole(1000);
    protected:
    int m_LevelID;
    std::vector<Enemy*> m_Enemies;
    std::vector<EnvironmentObject*> m_Environment;
    std::vector<std::pair<EnvironmentObjectInteractive*, Item*>> m_EnvironmentInteractive;
    std::vector<DrawableObject*> m_Drawables;
    std::vector<Lift*> m_Lifts;
    std::vector<EndPipeTop*> m_EndPipes;
    Character* m_Player;
    Vector2 m_PlayerSpawn;
    Vector2 m_CameraPosition = {0, 0};
    Ground* m_Ground;
    Background m_Background;
    const float m_PlayerOffset = 1000;
    bool isPlayerFinished = false;
    Vector2 m_ScreenSize = {1200, 900};
    MapLoader* m_MapLoader;
    private:
        bool m_Paused = false;
        EndPipeHandler m_EndPipeHandler;
        bool m_InControl = true;
    public:
        Level operator=(const Level& other) = delete;
        Level(const Level& other) = delete;
        void attachPlayer(Character* Player);
        virtual void update(float DeltaTime);
        virtual void render();
        void pauseLevel();
        void continueLevel();
        int GetLevelType() { return m_LevelID; };
    protected:
        void setOpeningScreenSize(int Width, int Height) { m_ScreenSize = Vector2{(float)Width, (float)Height}; };
        virtual void load() = 0;
        Level();
        virtual ~Level();
        void checkEnvironmentCollisions();
        void resolveEnvironmentCollisions();
        void resolveInteractiveEnvironmentCollisions();
        void handleItemLogic();
        void applyBoundaries();
        bool isPlayerInHole();
        void resolveHoleCollisions();
        unsigned int doPauseLogic();
        void resolveFlagPoleCollisions();
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
        Level* CreateLevel(int Type);
};
class Level101 : public Level
{
    friend class LevelFactory;
    private:
        Level101();
        ~Level101();
        void load() override;
        void update(float DeltaTime) override;
        void render() override;
        static Level101* GetLevel101();
};
class HiddenLevel101 : public Level
{
    private:
        HiddenLevel101();
        ~HiddenLevel101();
        void load() override;
        void update(float DeltaTime) override;
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
        void update(float DeltaTime) override;
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
        void load() override;
        void update(float DeltaTime) override;
        void render() override;
    public:
        static Level103* GetLevel103();
};
class Level102 : public Level
{
    friend class LevelFactory;
    private:
        Level102();
        ~Level102();
        void load() override;
        void update(float DeltaTime) override;
        void render() override;
    public:
        static Level102* GetLevel102();
};
class HiddenLevel102 : public Level
{
    private:
        HiddenLevel102();
        ~HiddenLevel102();
        void load() override;
        void update(float DeltaTime) override;
        void render() override;
    public:
        static HiddenLevel102* GetHiddenLevel102();
};
class HiddenLevel103 : public Level
{
    private:
        HiddenLevel103();
        ~HiddenLevel103();
        void load() override;
        void update(float DeltaTime) override;
        void render() override;
    public:
        static HiddenLevel103* GetHiddenLevel103();
};
