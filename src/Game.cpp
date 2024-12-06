#include "Game.hpp"

Game::Game() 
    : factory(LevelFactory::GetLevelFactory()), 
      level(factory.CreateLevel(LevelFactory::LEVEL_101)),
      character(ResourceManager::GetInstance()->GetTexture("mario"))
{
    // character = ResourceManager::GetInstance()->GetTexture("mario");
    // player = Character(&character, Vector2{10, 1}, 0.1f, 500.0f, 3.0f);
    player = new Mario;
    player->setPosition(Vector2{20, 0});  
    level->attachPlayer(player);  
}

Game::Game(int characterMenu, int levelMenu) 
    : factory(LevelFactory::GetLevelFactory()),  
      level(nullptr)  
{
    if (levelMenu == 0) {
        level = factory.CreateLevel(LevelFactory::LEVEL_101);
    }
    else if (levelMenu == 1) {
        level = factory.CreateLevel(LevelFactory::LEVEL_102);
    }
    else {
        level = factory.CreateLevel(LevelFactory::LEVEL_103);
    }
    
    
    if (characterMenu == 0) {
        character = ResourceManager::GetInstance()->GetTexture("mario");
    }
    else {
        character = ResourceManager::GetInstance()->GetTexture("mario");
    }

    player = new Mario;
    player->setPosition(Vector2{20, 0});
    level->attachPlayer(player);
}

Game::Game(const Game& other) 
    : factory(other.factory),  
      level(nullptr),          
      player(other.player)     
{
    if (other.level) {
        level = factory.CreateLevel(other.level->GetLevelType());
        if (level) {
            level->attachPlayer(player); 
        }
    }
}

Game& Game::operator=(const Game& other) {
    if (this == &other) {
        return *this; 
    }

    if (level) {
        level = nullptr;
    }

    factory = other.factory; 
    level = other.level ? other.factory.CreateLevel(other.level->GetLevelType()) : nullptr;

    player = other.player;

    return *this; 
}
void Game::start() {
    SetTargetFPS(60);  
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();  
        
        update(deltaTime);  
        draw();  
    }

    CloseWindow();  
}

void Game::update(float deltaTime) {
    level->update(deltaTime);  
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(WHITE);

    level->render();  

    EndDrawing();
}
