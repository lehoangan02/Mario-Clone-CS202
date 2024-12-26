#include "Game.hpp"
#include "ResourceManager.hpp"

Game::Game()  
    : factory(LevelFactory::GetLevelFactory()), 
      level(factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_102, this))
{
	player = CharacterFactory::createCharacter(CharacterType::MARIO);
    if (level == nullptr) {
        std::cerr << "Level is null" << std::endl;
    }
    std::cout << "Level Type: " << level -> GetLevelType() << std::endl;
    player->setPosition(Vector2{20, 0});  
    level->attachPlayer(player);  
    myFont = LoadFont("assets/Font/MarioFont.ttf");
    countdown = 300;
	timer = 0.0f;
	state = LEVEL_RETURN_MESSAGE::RUNNING;
    infoIcons.push_back(LoadTexture("assets/textures/CoinForBlueBG.png"));
	infoIcons.push_back(LoadTexture("assets/textures/fullHeart.png"));
	infoIcons.push_back(LoadTexture("assets/textures/noHeart.png"));
    MusicManager::getInstance().PlayMusic(MusicTrack::SuperBellHill);

    pauseButton = QuitButton(Rectangle{973, 20, 30, 30}, ResourceManager::GetInstance()->GetTexture("pause"));
    continueButton = QuitButton(Rectangle{467, 400, 30, 30}, ResourceManager::GetInstance()->GetTexture("continue"));
    homeButton = QuitButton(Rectangle{542, 400, 30, 30}, ResourceManager::GetInstance()->GetTexture("home"));
    homeButton2 = QuitButton(Rectangle{508, 400, 30, 30}, ResourceManager::GetInstance()->GetTexture("home"));

    pauseGame = ResourceManager::GetInstance()->GetTexture("pauseGame");
    winGame = ResourceManager::GetInstance()->GetTexture("winGame");
    loseGame = ResourceManager::GetInstance()->GetTexture("loseGame");

    state = LEVEL_RETURN_MESSAGE::RUNNING;
    isSaveScore = false;
}

Game::Game(int characterMenu, int levelMenu) 
    : factory(LevelFactory::GetLevelFactory()),  
      level(nullptr)  
{
    if (characterMenu == 0) {
        player = CharacterFactory::createCharacter(CharacterType::MARIO);;
    } else {
        player = CharacterFactory::createCharacter(CharacterType::LUIGI);
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
    else if (levelMenu == 5) {
        level = factory.CreateLevel(LevelFactory::LEVEL_TESTING, this);
    }
    level -> reset();
    player->setPosition(Vector2{200, 0});
    level->attachPlayer(player);

    countdown = 300;
	timer = 0.0f;
    infoIcons.push_back(LoadTexture("assets/textures/CoinForBlueBG.png"));
	infoIcons.push_back(LoadTexture("assets/textures/fullHeart.png"));
	infoIcons.push_back(LoadTexture("assets/textures/noHeart.png"));
    MusicManager::getInstance().PlayMusic(MusicTrack::SuperBellHill);

    pauseButton = QuitButton(Rectangle{973, 20, 30, 30}, ResourceManager::GetInstance()->GetTexture("pause"));
    continueButton = QuitButton(Rectangle{467, 369, 30, 30}, ResourceManager::GetInstance()->GetTexture("continue"));
    homeButton2 = QuitButton(Rectangle{508, 369, 30, 30}, ResourceManager::GetInstance()->GetTexture("replay"));
    homeButton = QuitButton(Rectangle{542, 369, 30, 30}, ResourceManager::GetInstance()->GetTexture("home"));

    pauseGame = ResourceManager::GetInstance()->GetTexture("pauseGame");
    winGame = ResourceManager::GetInstance()->GetTexture("winGame");
    loseGame = ResourceManager::GetInstance()->GetTexture("loseGame");


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
    isSaveScore = false;
}

void Game::save(const std::string& filename)  {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File not opened" << std::endl;
        return;
    }
    if (level->GetLevelType() == LevelFactory::LEVEL_101) {
        file  << "0 ";
    } else if (level->GetLevelType() == LevelFactory::LEVEL_102) {
        file << "1 ";
    } else if (level->GetLevelType() == LevelFactory::LEVEL_103) {
        file << "2 ";
    } else if (level->GetLevelType() == LevelFactory::HIDDEN_LEVEL_101) {
        file << "3 ";
    } else if (level->GetLevelType() == LevelFactory::HIDDEN_LEVEL_102) {
        file << "4 ";
    }
    else if (level->GetLevelType() == LevelFactory::LEVEL_TESTING) {
        file << "5 ";
    }

    if (player->getType() == CharacterType::MARIO) {
        file <<"0 ";
    } else {
        file <<"1 ";
    }

    Vector2 position = player->GetPosition();
    file << position.x << " " << position.y << " ";
    file << player->getScore() << " ";
    file << player->getCoins() << " ";
    file << player->getLives() << " ";
    file << countdown << " ";
    file.close();
}

void Game::saveScore(const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "File not found" << std::endl;
        return;
    }
    file << player->getScore() << std::endl;
    file.close();
}
void Game::change(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File not found" << std::endl;
        return;
    }
    int level, character, score, coins, lives, time;
    float x, y;
    file >> level >> character >> x >> y >> score >> coins >> lives >> time;
    if (character == 0) {
        player = CharacterFactory::createCharacter(CharacterType::MARIO);;
    } else {
        player = CharacterFactory::createCharacter(CharacterType::LUIGI);
    }

    if (level == 0) {
        this->level = factory.CreateLevel(LevelFactory::LEVEL_101, this);
    } else if (level == 1) {
        this->level = factory.CreateLevel(LevelFactory::LEVEL_102, this);
    } else if (level == 2) {
        this->level = factory.CreateLevel(LevelFactory::LEVEL_103, this);
    }
    else if (level == 3) {
        this->level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_101, this);
    }
    else if (level == 4) {
        this->level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_102, this);
    }
    else if (level == 5) {
        this->level = factory.CreateLevel(LevelFactory::LEVEL_TESTING, this);
    }
    this->level->reset();
    player->reset();
    player->setPosition(Vector2{x * 1.0f, y * 1.0f});
    this->player->setScore(score);
    this->player->setLives(lives);
    this->player->setCoins(coins);
    this->countdown = time;
    this->timer = 0.0f;
    this->level->attachPlayer(player);

    MusicManager::getInstance().PlayMusic(MusicTrack::SuperBellHill);


    int levelType = this->level->GetLevelType();

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
    file.close();
    isSaveScore = false;
}

void Game::changeMenu(int characterMenu, int levelMenu) {
    if (characterMenu == 0) {
        player = CharacterFactory::createCharacter(CharacterType::MARIO);;
    } else {
        player = CharacterFactory::createCharacter(CharacterType::LUIGI);
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
    else if (levelMenu == 5) {
        level = factory.CreateLevel(LevelFactory::LEVEL_TESTING, this);
    }
    player->setPosition(Vector2{20, 0});
    level->attachPlayer(player);

    countdown = 300;
    timer = 0.0f;
    MusicManager::getInstance().PlayMusic(MusicTrack::SuperBellHill);


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
    }

    isSaveScore = false;
}

void Game::reset(int characterMenu) {
    if (characterMenu == 0) {
        player = CharacterFactory::createCharacter(CharacterType::MARIO);;
    } else {
        player = CharacterFactory::createCharacter(CharacterType::LUIGI);
    }
    player -> reset();
    level = factory.CreateLevel(LevelFactory::LEVEL_101, this);
    level->attachPlayer(player);
    player->setPosition(Vector2{200, 0});
    countdown = 300;
    timer = 0.0f;
    MusicManager::getInstance().PlayMusic(MusicTrack::SuperBellHill);
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
   
    handleState();
    update(GetFrameTime());
    MusicManager::getInstance().UpdateMusic();
    draw();
    if (IsKeyPressed(KEY_A)) {
        state = LEVEL_RETURN_MESSAGE::QUIT;
    }
    else if (IsKeyDown(KEY_B)) {
        state = LEVEL_RETURN_MESSAGE::LOSE;
    }
    else if (IsKeyPressed(KEY_C)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        state = LEVEL_RETURN_MESSAGE::WIN;
    }
        
}

void Game::update(float deltaTime) {
    if (level) {
        level->update(deltaTime);
    }
    if (pauseButton.isClicked()) {
        state = LEVEL_RETURN_MESSAGE::PAUSE;
    } else if (continueButton.isClicked()) {
         state = LEVEL_RETURN_MESSAGE::CONTINUE;
    } else if (homeButton2.isClicked()) {
        save("./continue.txt");
        state = LEVEL_RETURN_MESSAGE::QUIT;
    } else if (homeButton.isClicked()) {
        save("./continue.txt");
        state = LEVEL_RETURN_MESSAGE::QUIT;
    }
}

void Game::draw() {
    // BeginDrawing();
    // ClearBackground(RAYWHITE);
    if (level) {
        level->render();
    }
    if (state == LEVEL_RETURN_MESSAGE::PAUSE) {
        drawContinueButton();
    } else if (state == LEVEL_RETURN_MESSAGE::CONTINUE) {
        drawPauseMenu();
    } else if (state == LEVEL_RETURN_MESSAGE::WIN && level->GetLevelType() == LevelFactory::LEVEL_103) {
        drawWinButton();
    } else if (state == LEVEL_RETURN_MESSAGE::LOSE) {
        drawLoseButton();
    }
    else if (state == LEVEL_RETURN_MESSAGE::RUNNING) {
        drawPauseMenu();
    }
    drawInfo();
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
            restartLevel();
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
        state = LEVEL_RETURN_MESSAGE::RUNNING;
    }
     else if (level->GetLevelType() == LevelFactory::LEVEL_102) {
        level = factory.CreateLevel(LevelFactory::LEVEL_103, this);
        level -> reset();
        MusicManager::getInstance().PlayMusic(MusicTrack::Athletic);
        state = LEVEL_RETURN_MESSAGE::RUNNING;
    } 
    else {
        return;
    }
    player->setPosition(Vector2{20, 0});
    level->attachPlayer(player);
    level->update(0.01f);
    state = LEVEL_RETURN_MESSAGE::RUNNING; 
	resetCountdown();
}

void Game::hiddenLevel() {
    player->reset();
    if (level->GetLevelType() == LevelFactory::LEVEL_101) 
    {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_101, this);
        level -> reset();
        level->attachPlayer(player);
        player->setPosition(Vector2{200, 0});
        MusicManager::getInstance().PlayMusic(MusicTrack::UnderGround);
    }
    else if (level->GetLevelType() == LevelFactory::LEVEL_102) 
    {
        level = factory.CreateLevel(LevelFactory::HIDDEN_LEVEL_102, this);
        level -> reset();
        level->attachPlayer(player);
        player->setPosition(Vector2{200, 0});
        MusicManager::getInstance().PlayMusic(MusicTrack::SMB);
    }
    else if (level->GetLevelType() == LevelFactory::HIDDEN_LEVEL_101)
    {
        level = factory.CreateLevel(LevelFactory::LEVEL_101, this);
        level -> reset();
        level->attachPlayer(player);
        player->setPosition(Vector2{14850, 35});
        std::cout << "Set Position: " << 14800 << " " << 35 << std::endl;
        MusicManager::getInstance().PlayMusic(MusicTrack::SuperBellHill);

    }
    else if (level->GetLevelType() == LevelFactory::HIDDEN_LEVEL_102)
    {
        level = factory.CreateLevel(LevelFactory::LEVEL_102, this);
        level -> reset();
        level->attachPlayer(player);
        player->setPosition(Vector2{5100, 175});
        std::cout << "Set Position: " << 5100 << " " << 175 << std::endl;
        MusicManager::getInstance().PlayMusic(MusicTrack::FlowerGarden);
    }
    else return;
    level->update(0.01f);
    state = LEVEL_RETURN_MESSAGE::RUNNING; 
}

void Game::restartLevel() {
    level->reset();
    // level->attachPlayer(player);
    // level->update(0.01f);
	resetCountdown();
	MusicManager::getInstance().PlayCurrentTrack();
    state = LEVEL_RETURN_MESSAGE::RUNNING;
}

void Game::handleState() {
    switch (state) {
        case LEVEL_RETURN_MESSAGE::HIDDEN:
            hiddenLevel();
            break;
        case LEVEL_RETURN_MESSAGE::WIN:
            if (level->GetLevelType() == LevelFactory::LEVEL_103) {
                level->pauseLevel();
                if (!isSaveScore) {
                    saveScore("score.txt");
                    isSaveScore = true;
                }
            }
            else nextLevel();
            break;
        case LEVEL_RETURN_MESSAGE::LOSE:
            if (!isSaveScore) {
                saveScore("score.txt");
                isSaveScore = true;
            }
            level->pauseLevel();
            break;
        case LEVEL_RETURN_MESSAGE::QUIT:
            //level->reset();
            break;
        case LEVEL_RETURN_MESSAGE::RESTART:
            restartLevel();
            break;
        case LEVEL_RETURN_MESSAGE::PAUSE:
            level->pauseLevel();
            break;
        case LEVEL_RETURN_MESSAGE::CONTINUE:
            level->continueLevel();
            state = LEVEL_RETURN_MESSAGE::RUNNING;
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

    if (state != LEVEL_RETURN_MESSAGE::PAUSE && state != LEVEL_RETURN_MESSAGE::WIN && state != LEVEL_RETURN_MESSAGE::LOSE) {
        float deltaTime;
        deltaTime = GetFrameTime(); 
        timer += deltaTime;
        if (timer >= 1.0f) {
            countdown--;
            timer = 0.0f; 
            if (countdown <= 0) {
                countdown = 0;
				state = LEVEL_RETURN_MESSAGE::LOSE;
            }
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
    static bool display = true;
    if (IsKeyPressed(KEY_U)) {
        display = !display;
    }
    if (!display) return;
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

void Game::drawPauseMenu() {
    pauseButton.draw(YELLOW);
}

void Game::drawContinueButton() {
    DrawTextureEx(pauseGame, {317, 255}, 0.0f, 0.125f, RAYWHITE);
    continueButton.draw(RAYWHITE);
    homeButton.draw();
}

void Game::drawWinButton() {
    DrawTextureEx(winGame, {317, 255}, 0.0f, 0.125f, RAYWHITE);
    homeButton2.draw();
}

void Game::drawLoseButton() {
    DrawTextureEx(loseGame, {317, 255}, 0.0f, 0.125f, RAYWHITE);
    homeButton2.draw();
}
void Game::reset()
{
    player -> reset();
	level = factory.CreateLevel(level->GetLevelType(), this);
    level -> reset();
    level->attachPlayer(player);
    player->setPosition(Vector2{200, 0});
    countdown = 300;
    timer = 0.0f;
    state = LEVEL_RETURN_MESSAGE::RUNNING;
}

void Game::resetCountdown() {
	countdown = 300;
}