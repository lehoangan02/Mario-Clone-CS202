#include "Game.hpp"

Game::Game() 
    : factory(LevelFactory::GetLevelFactory()), 
      level(factory.CreateLevel(LevelFactory::LEVEL_101)),
      player(nullptr, Vector2{10, 1}, 0.1f, 500.0f, 3.0f)  
{
    Texture t = LoadTexture("assets/textures/mario.png");  
    player.setPosition(Vector2{20, 0});  
    level->attachPlayer(&player);  
}

Game::Game(int characterMenu, int levelMenu) {
    factory = LevelFactory::GetLevelFactory();
    if (levelMenu == 0) {
        level = factory.CreateLevel(LevelFactory::LEVEL_101);
    }
    else if (levelMenu == 1) {
        level = factory.CreateLevel(LevelFactory::LEVEL_102);
    }
    else level = factory.CreateLevel(LevelFactory::LEVEL_103);


    Texture t;
    if (characterMenu == 0) {
        t = LoadTexture("assets/textures/mario.png");
    }
    else t = LoadTexture("assets/textures/luigi.png");

    player = Character(&t, Vector2{10, 1}, 0.1f, 500.0f, 3.0f);
    player.setPosition(Vector2{20, 0});  
    level->attachPlayer(&player);
}

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
