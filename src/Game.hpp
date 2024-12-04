
#ifndef GAME_hpp
#define GAME_hpp

#include "GUI.hpp"
#include "./characters/Character.h"
#include "./levels/Level.hpp"
#include "./animation/Animation.h"

class Game {
private:
    LevelFactory& factory;
    Level* level;
    Character player;  

public:
    Game();

    Game(int characterMenu, int levelMenu);

    Game& operator=(const Game& other);
   
    Game(const Game& other);
    void start();  
    void update(float deltaTime);  
    void draw();  
};

#endif /* GAME_hpp */


