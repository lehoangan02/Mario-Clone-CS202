#include "Game.hpp"

Game::Game() 
    : factory(LevelFactory::GetLevelFactory()), 
      level(factory.CreateLevel(LevelFactory::LEVEL_101))
{
    player = new Mario;
    std::cout << "Level Type: " << level -> GetLevelType() << std::endl;
    player->setPosition(Vector2{20, 0});  
    level->attachPlayer(player);
    MusicManager::getInstance().PlayMusic(MusicTrack::SuperBellHill);
}

Game::Game(int characterMenu, int levelMenu) 
    : factory(LevelFactory::GetLevelFactory()),  
      level(nullptr)  
{
    if (characterMenu == 0) {
        player = new Mario;
    } else {
        player = new Luigi;
    }

    if (levelMenu == 0) {
        level = factory.CreateLevel(LevelFactory::LEVEL_101);
    } else if (levelMenu == 1) {
        level = factory.CreateLevel(LevelFactory::LEVEL_102);
    } else if (levelMenu == 2) {
        level = factory.CreateLevel(LevelFactory::LEVEL_103);
    }
    else if (levelMenu == 3) {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_101);
    }
    else if (levelMenu == 4) {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_102);
    }
    player->setPosition(Vector2{20, 0});
    level->attachPlayer(player);
    int levelType = level->GetLevelType();
    switch (levelType)
    {
    case LevelFactory::LEVEL_101:
        MusicManager::getInstance().PlayMusic(MusicTrack::SuperBellHill);
        break;
    case LevelFactory::LEVEL_102:
        MusicManager::getInstance().PlayMusic(MusicTrack::FlowerGarden);
        break;
    case LevelFactory::LEVEL_103:
        MusicManager::getInstance().PlayMusic(MusicTrack::Athletic);
        break;
    case LevelFactory::HIDDEN_LEVEL_101:
        MusicManager::getInstance().PlayMusic(MusicTrack::UnderGround);
        break;
    case LevelFactory::HIDDEN_LEVEL_102:
        MusicManager::getInstance().PlayMusic(MusicTrack::SMB);
        break;
        
    default:
        break;
    }
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
    MusicManager::getInstance().UpdateMusic();
    draw();
    if (IsKeyDown(KEY_A)) {
        nextLevel();
    }
    else if (IsKeyDown(KEY_B)) {
        hiddenLevel();
    }
    else if (IsKeyDown(KEY_C)) {
        restartLevel();
    }
}

void Game::update(float deltaTime) {
    if (level) {
        level->update(deltaTime);
    }
    // if (player.GetType() == Character::MARIO) {
    //     player->update(deltaTime);
    // }
    // else if (player.GetType() == Character::LUIGI) {
    //     player->update(deltaTime);
    
}

void Game::draw() {
    if (level) {
        level->render();
    }
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
        case 7:
            state = LEVEL_RETURN_MESSAGE::RESTART;
            break;
        default:
            break;
    }
}


void Game::nextLevel() {
    if (level->GetLevelType() == LevelFactory::LEVEL_101) {     
        level = factory.CreateLevel(LevelFactory::LEVEL_102);
        level -> reset();
        MusicManager::getInstance().PlayMusic(MusicTrack::FlowerGarden);
    }
     else if (level->GetLevelType() == LevelFactory::LEVEL_102) {
        level = factory.CreateLevel(LevelFactory::LEVEL_103);
        level -> reset();
        MusicManager::getInstance().PlayMusic(MusicTrack::Athletic);
    } 
    else {
        //draw menu win
        state = LEVEL_RETURN_MESSAGE::RESTART;
        return;
    }

    //delete player;
    //player = new Mario;
    player->setPosition(Vector2{20, 0});
    level->attachPlayer(player);
    level->update(0.01f);
    state = LEVEL_RETURN_MESSAGE::RUNNING; 
}

void Game::hiddenLevel() {
    if (level->GetLevelType() == LevelFactory::LEVEL_101) 
    {
        
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_101);
        level -> reset();
        MusicManager::getInstance().PlayMusic(MusicTrack::UnderGround);
    }
    else if (level->GetLevelType() == LevelFactory::LEVEL_102) 
    {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_102);
        level -> reset();
        MusicManager::getInstance().PlayMusic(MusicTrack::SMB);
    }
    else if (level->GetLevelType() == LevelFactory::LEVEL_103) 
    {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_103);
        level -> reset();
    }
    else return;

    player->setPosition(Vector2{20, 0});
    level->attachPlayer(player);
    level->update(0.01f);
    state = LEVEL_RETURN_MESSAGE::RUNNING; 
}

void Game::restartLevel() {
    level = factory.CreateLevel(level->GetLevelType());
    level -> reset();
    player->setPosition(Vector2{20, 0});
    level->attachPlayer(player);
    level->update(0.01f);
}

void Game::handleState() {
    switch (state) {
        case LEVEL_RETURN_MESSAGE::PAUSE:
            //drawPauseMenu();
            level->pauseLevel();
            break;
        case LEVEL_RETURN_MESSAGE::CONTINUE:
            level->continueLevel();
            //drawContinueButton();
            break;
        case LEVEL_RETURN_MESSAGE::RUNNING:
            level->continueLevel();
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
            level->pauseLevel();
            break;
        case LEVEL_RETURN_MESSAGE::QUIT:
            break;
        case LEVEL_RETURN_MESSAGE::RESTART:
            restartLevel();
            break;
    }
}