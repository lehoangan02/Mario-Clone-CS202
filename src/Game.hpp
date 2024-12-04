
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
//     Game& Game::operator=(const Game& other) {
//     if (this == &other) {
//         return *this; 
//     }

//     if (level) {
//         level = nullptr;
//     }

//     factory = other.factory; 
//     level = other.level ? other.factory.CreateLevel(other.level->GetLevelType()) : nullptr;

//     player = other.player;

//     return *this; 
// }
  
    Game::Game(const Game& other) 
    : factory(other.factory),  
      level(nullptr),          
      player(other.player)     
{
    if (other.level) {
        level = factory.CreateLevel(other.level->GetLevelType());
        if (level) {
            level->attachPlayer(&player); 
        }
    }
}

    void start();  
    void update(float deltaTime);  
    void draw();  
};

#endif /* GAME_hpp */


