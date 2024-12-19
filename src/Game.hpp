
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

    void nextLevel();
    void hiddenLevel();
    void restartLevel();

    // Implement notify method
    void notify(Component* sender, LEVEL_RETURN_MESSAGE eventCode) override;

    // Methods to handle game states
    void handleState();
    void drawPauseMenu();
    void drawContinueButton();
    void drawWinButton();
    void drawLoseButton();
    void drawQuitButton();

    LEVEL_RETURN_MESSAGE getState() { return state; };
};

#endif /* GAME_hpp */