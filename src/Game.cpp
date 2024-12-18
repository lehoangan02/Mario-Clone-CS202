#include "Game.hpp"

Game::Game() 
    : factory(LevelFactory::GetLevelFactory()), 
      level(factory.CreateLevel(LevelFactory::LEVEL_101))
{
    player = new Mario;
    std::cout << "Level Type: " << level -> GetLevelType() << std::endl;
    player->setPosition(Vector2{20, 0});  
    level->attachPlayer(player);  
}

Game::Game(int characterMenu, int soundMenu) 
    : factory(LevelFactory::GetLevelFactory()),  
      level(nullptr)  
{
    if (characterMenu == 0) {
        player = new Mario;
    } else {
        player = new Luigi;
    }
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
    update(GetFrameTime());
    draw();
    if (IsKeyDown(KEY_N)) {
        nextLevel();
    }
    else if (IsKeyDown(KEY_O)) {
        hiddenLevel();
    }
}

void Game::update(float deltaTime) {
    if (level) {
        level->update(deltaTime);
    }
}

void Game::draw() {
    if (level) {
        level->render();
    }
}

void Game::notify(Component* sender, LEVEL_RETURN_MESSAGE eventCode) {
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


void Game::nextLevel() {
    if (level->GetLevelType() == LevelFactory::LEVEL_101) {     
        level = factory.CreateLevel(LevelFactory::LEVEL_102);
    }
     else if (level->GetLevelType() == LevelFactory::LEVEL_102) {
         level = factory.CreateLevel(LevelFactory::LEVEL_103);
    } 
    else return;

    //delete player;
    //player = new Mario;
    player->setPosition(Vector2{20, 0});
    level->update(0.01f);
    level->attachPlayer(player);
    state = LEVEL_RETURN_MESSAGE::RUNNING; 
}

void Game::hiddenLevel() {
    if (level->GetLevelType() == LevelFactory::LEVEL_101) 
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_101);
    else if (level->GetLevelType() == LevelFactory::LEVEL_102) 
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_102);
    else if (level->GetLevelType() == LevelFactory::LEVEL_103) 
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_103);
    else return;

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