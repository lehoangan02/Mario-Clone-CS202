#include "Game.hpp"

Game::Game() 
    : factory(LevelFactory::GetLevelFactory()), 
      level(factory.CreateLevel(LevelFactory::LEVEL_101)),
      character(ResourceManager::GetInstance()->GetTexture("mario"))
{
    // character = ResourceManager::GetInstance()->GetTexture("mario");
    // player = Character(&character, Vector2{10, 1}, 0.1f, 500.0f, 3.0f);
    player = new Mario;
    std::cout << "Level Type: " << level -> GetLevelType() << std::endl;
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
    while (!WindowShouldClose()) {
        update(GetFrameTime());
		MusicManager::getInstance().UpdateMusic();
        draw();
        if (IsKeyDown(KEY_N)) {
            nextLevel();
        }
        else if (IsKeyDown(KEY_O)) {
            hiddenLevel();
        }
    }
    CloseWindow();
}

void Game::update(float deltaTime) {
    if (level) {
        level->update(deltaTime);
    }
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (level) {
        level->render();
    }
    EndDrawing();
}



void Game::notify(Component* sender, int eventCode) {
    switch (eventCode) {
        case 0:
            state = LEVEL_RETURN_MESSAGE::PAUSE;
            break;
        case 1:
            state = LEVEL_RETURN_MESSAGE::CONTINUE;
            break;
        case 2:
            state = LEVEL_RETURN_MESSAGE::RUNNING;
            break;
        case 3:
            state = LEVEL_RETURN_MESSAGE::HIDDEN;
            break;
        case 4:
            state = LEVEL_RETURN_MESSAGE::WIN;
            break;
        case 5:
            state = LEVEL_RETURN_MESSAGE::LOSE;
            break;
        case 6:
            state = LEVEL_RETURN_MESSAGE::QUIT;
            break;
        default:
            break;
    }
}

void Game::pause() {
    notify(nullptr, 0); // Pause event
}

void Game::resume() {
    notify(nullptr, 1); // Continue event
}

void Game::win() {
    notify(nullptr, 4); // Win event
}

void Game::lose() {
    notify(nullptr, 5); // Lose event
}

void Game::quit() {
    notify(nullptr, 6); // Quit event
}

void Game::nextLevel() {
    // Logic to switch to the next level
    if (level->GetLevelType() == LevelFactory::LEVEL_101) {     
        level = factory.CreateLevel(LevelFactory::LEVEL_103);
    // } else if (level->GetLevelType() == LevelFactory::LEVEL_102) {
    //     level = factory.CreateLevel(LevelFactory::LEVEL_103);
    } else {
    }
    player->setPosition(Vector2{20, 0});
    level->update(0.0f);
    level->attachPlayer(player);
    state = LEVEL_RETURN_MESSAGE::RUNNING; 
}

void Game::hiddenLevel() {
    if (level->GetLevelType() == LevelFactory::LEVEL_101) 
        level = factory.CreateLevel(LevelFactory::LEVEL_103);
    // else if (level->GetLevelType() == LevelFactory::LEVEL_102) 
    //     level = factory.CreateLevel(LevelFactory::LEVEL_103);
    else if (level->GetLevelType() == LevelFactory::LEVEL_103) 
        level = factory.CreateLevel(LevelFactory::LEVEL_103);
    player->setPosition(Vector2{20, 0});
    level->update(0.0f);
    level->attachPlayer(player);
    state = LEVEL_RETURN_MESSAGE::RUNNING; 
}

void Game::handleState() {
    switch (state) {
        case LEVEL_RETURN_MESSAGE::PAUSE:
            //drawPauseMenu();
            break;
        case LEVEL_RETURN_MESSAGE::CONTINUE:
            // Handle continue state
            break;
        case LEVEL_RETURN_MESSAGE::RUNNING:
            // Handle running state
            break;
        case LEVEL_RETURN_MESSAGE::HIDDEN:
            hiddenLevel();
            break;
        case LEVEL_RETURN_MESSAGE::WIN:
            nextLevel();
            break;
        case LEVEL_RETURN_MESSAGE::LOSE:
            //drawLoseButton();
            break;
        case LEVEL_RETURN_MESSAGE::QUIT:
            //drawQuitButton();
            break;
    }
}