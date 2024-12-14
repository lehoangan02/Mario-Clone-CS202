
#ifndef GAME_hpp
#define GAME_hpp

#include "GUI.hpp"
#include "./characters/Character.h"
#include "./levels/Level.hpp"
#include "./animation/Animation.h"
#include "./Mediator/Mediator.hpp"
#include "ResourceManager.hpp"

class Game : public Mediator {
private:
    LevelFactory& factory;
    Level* level;
    Texture2D character;
    Character* player;
    LEVEL_RETURN_MESSAGE state;

public:
    Game();
    Game(int characterMenu, int levelMenu);
    Game& operator=(const Game& other);
    Game(const Game& other);
    void start();
    void update(float deltaTime);
    void draw();

    void pause();
    void resume();
    void win();
    void lose();
    void quit();
    void nextLevel();

    // Implement notify method
    void notify(Component* sender, int eventCode) override;

    // Methods to handle game states
    void handleState();
    void drawPauseMenu();
    void drawContinueButton();
    void drawWinButton();
    void drawLoseButton();
    void drawQuitButton();
    void test() {
        if(IsKeyDown(KEY_A)) {
            notify(nullptr, 0);
        }
        else if(IsKeyDown(KEY_B)) {
            notify(nullptr, 1);
        }
        else if(IsKeyDown(KEY_C)) {
            notify(nullptr, 2);
        }
        else if(IsKeyDown(KEY_D)) {
            notify(nullptr, 3);
        }
        else if(IsKeyDown(KEY_E)) {
            notify(nullptr, 4);
        }
        else if(IsKeyDown(KEY_F)) {
            notify(nullptr, 5);
        }
        else if(IsKeyDown(KEY_G)) {
            notify(nullptr, 6);
        }
    }
};

#endif /* GAME_hpp */