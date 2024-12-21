#include "Game.hpp"

Game::Game() 
    : factory(LevelFactory::GetLevelFactory()), 
      level(factory.CreateLevel(LevelFactory::LEVEL_101, this))
{
    player = new Mario;
    if (level == nullptr) {
        std::cerr << "Level is null" << std::endl;
    }
    std::cout << "Level Type: " << level -> GetLevelType() << std::endl;
    myFont = LoadFont("assets/Font/MarioFont.ttf");
    countdown = 400;
	timer = 0.0f;
    infoIcons.push_back(LoadTexture("assets/textures/CoinForBlueBG.png"));
	infoIcons.push_back(LoadTexture("assets/textures/fullHeart.png"));
	infoIcons.push_back(LoadTexture("assets/textures/noHeart.png"));
    level-> reset();
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
        level = factory.CreateLevel(LevelFactory::LEVEL_101, this);
    } else if (levelMenu == 1) {
        level = factory.CreateLevel(LevelFactory::LEVEL_102, this);
    } else if (levelMenu == 2) {
        level = factory.CreateLevel(LevelFactory::LEVEL_103, this);
    }
    else if (levelMenu == 3) {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_101, this);
    }
    else if (levelMenu == 4) {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_102, this);
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
        level = factory.CreateLevel(other.level->GetLevelType(), this);
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
    level = other.level ? other.factory.CreateLevel(other.level->GetLevelType(), this) : nullptr;

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
	drawInfo();
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
        level = factory.CreateLevel(LevelFactory::LEVEL_102, this);
        level -> reset();
        MusicManager::getInstance().PlayMusic(MusicTrack::FlowerGarden);
    }
     else if (level->GetLevelType() == LevelFactory::LEVEL_102) {
        level = factory.CreateLevel(LevelFactory::LEVEL_103, this);
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
        
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_101, this);
        level -> reset();
        MusicManager::getInstance().PlayMusic(MusicTrack::UnderGround);
    }
    else if (level->GetLevelType() == LevelFactory::LEVEL_102) 
    {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_102, this);
        level -> reset();
        MusicManager::getInstance().PlayMusic(MusicTrack::SMB);
    }
    else if (level->GetLevelType() == LevelFactory::LEVEL_103) 
    {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_103, this);
        level -> reset();
    }
    else return;

    player->setPosition(Vector2{20, 0});
    level->attachPlayer(player);
    level->update(0.01f);
    state = LEVEL_RETURN_MESSAGE::RUNNING; 
}

void Game::restartLevel() {
    level = factory.CreateLevel(level->GetLevelType(), this);
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

void Game::drawInfo() {
	int score = player->getScore();
    int coins = player->getCoins();
	int world = level->GetLevelType();
    std::string worldString;
	if (world == LevelFactory::LEVEL_101 || world == LevelFactory::HIDDEN_LEVEL_101 ) {
		worldString = "1-1";
	}
    else if (world == LevelFactory::LEVEL_102 || world == LevelFactory::HIDDEN_LEVEL_102 || world == LevelFactory::HIDDEN_LEVEL_112) {
        worldString = "1-2";
    }
    else if (world == LevelFactory::LEVEL_103 || world == LevelFactory::HIDDEN_LEVEL_103) {
        worldString = "1-3";
    }
    float deltaTime;
    deltaTime = GetFrameTime(); 
    timer += deltaTime;
    if (timer >= 1.0f) {
        countdown--;
        timer = 0.0f; 
        if (countdown <= 0) {
            countdown = 0;
        }
    }

	int lives = player->getLives(); 
	const int sectionWidth = SCREEN_WIDTH / 6;
    Vector2 sectionPositions[5] = {
        { sectionWidth * 0.5f, 20 },  // SCORE
        { sectionWidth * 1.5f, 20 },  // COINS
        { sectionWidth * 2.5f, 20 },  // WORLD
        { sectionWidth * 3.5f, 20 },  // TIME
        { sectionWidth * 4.5f, 20 }   // LIVES
    };
    DrawTextCentered(myFont, "SCORE", std::to_string(score), sectionPositions[0], 24, 1, WHITE);
    DrawTextCentered(myFont, "COINS", "x", sectionPositions[1], 24, 1, WHITE);
    DrawTextureEx(infoIcons[0], { sectionPositions[1].x - 40, sectionPositions[1].y + 28 }, 0.0f, 2.0f, WHITE);
    DrawTextEx(myFont, std::to_string(coins).c_str(), {sectionPositions[1].x + 15, sectionPositions[1].y + 30}, 24, 1, WHITE);
    DrawTextCentered(myFont, "WORLD", worldString, sectionPositions[2], 24, 1, WHITE);
    DrawTextCentered(myFont, "TIME", std::to_string(countdown), sectionPositions[3], 24, 1, WHITE);
    DrawTextCentered(myFont, "LIVES", "", sectionPositions[4], 24, 1, WHITE);
    float spacing = 2.0f;
	float HeartWidth = infoIcons[1].width;
    float maxLives = 5.0f;
	float startPos = sectionPositions[4].x - maxLives / 2.0f * HeartWidth - 2*spacing ;
    for (int i = 0; i < lives; i++) DrawTexture(infoIcons[1], startPos + i * HeartWidth + i* spacing, sectionPositions[4].y + 25, WHITE);
	for (int i = lives; i < 5; i++) DrawTexture(infoIcons[2], startPos + i * HeartWidth + i * spacing, sectionPositions[4].y + 25, WHITE);
}

void Game::DrawTextCentered(Font font, const std::string& label, const std::string& value, Vector2 position, float fontSize, float spacing, Color color) {
    float labelWidth = MeasureTextEx(font, label.c_str(), fontSize, spacing).x;
    float valueWidth = MeasureTextEx(font, value.c_str(), fontSize, spacing).x;
    DrawTextEx(font, label.c_str(), { position.x - labelWidth / 2, position.y }, fontSize, spacing, color);
    DrawTextEx(font, value.c_str(), { position.x - valueWidth / 2, position.y + 30 }, fontSize, spacing, color);
}