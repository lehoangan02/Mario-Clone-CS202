#include "Level.hpp"
LevelFactory& LevelFactory::GetLevelFactory()
{
    static LevelFactory Factory;
    return Factory;
}
Level* LevelFactory::CreateLevel(LevelType Type)
{
    switch (Type)
    {
        case LEVEL_101:
            return Level101::GetLevel101();
            break;
        case LEVEL_TESTING:
            return LevelTesting::GetLevelTesting();
            break;
        case LEVEL_103:
            return Level103::GetLevel103();
            break;
        
    }
}
Level::Level()
{
    m_CameraPosition = {0, 0};
    m_Ground = Ground::GetGround();
}
Level::~Level()
{
    for (auto& object : m_Environment)
    {
        delete object;
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        delete object;
    }
    for (auto& object : m_Drawables)
    {
        delete object;
    }
    for (auto& object : m_Lifts)
    {
        delete object;
    }
    for (auto& object : m_EndPipes)
    {
        delete object;
    }

}
void Level::attachPlayer(Character* Player)
{
    m_Player = Player;
}
void Level::checkEnvironmentCollisions()
{
}
void Level::resolveEnvironmentCollisions()
{
    for (int i = 0; i < m_Environment.size(); i++)
    {
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        AABBox EnvironmentBox = AABBox(m_Environment[i]->m_Position, m_Environment[i]->getSize());
        EnvironmentBox.setFixed(true);
        if (isColliding(PlayerBox, EnvironmentBox))
        {
            if (isCollidingOnVertically(PlayerBox, EnvironmentBox))
            {
                m_Player->resetVelocity();
                if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                {
                    m_Player->onPlatform();
                }
            }
            resolveCollisions(PlayerBox, EnvironmentBox);
            m_Player->setPosition(PlayerBox.getPosition());
            m_Environment[i]->m_Position = EnvironmentBox.getPosition();
        }
    }
    for (int i = 0; i < m_Lifts.size(); i++)
    {
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        AABBox EnvironmentBox = AABBox(m_Lifts[i]->m_Position, m_Lifts[i]->getSize());
        EnvironmentBox.setFixed(true);
        if (isColliding(PlayerBox, EnvironmentBox))
        {
            if (isCollidingOnVertically(PlayerBox, EnvironmentBox))
            {
                m_Player->resetVelocity();
                if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                {
                    m_Player->onPlatform();
                }
            }
            resolveCollisions(PlayerBox, EnvironmentBox);
            m_Player->setPosition(PlayerBox.getPosition());
            m_Lifts[i]->m_Position = EnvironmentBox.getPosition();
        }
    }
    for (int i = 0; i < m_EndPipes.size(); ++i)
    {
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        AABBox EnvironmentBox = AABBox(m_EndPipes[i]->m_Position, m_EndPipes[i]->getSize());
        EnvironmentBox.setFixed(true);
        if (isColliding(PlayerBox, EnvironmentBox))
        {
            if (isCollidingOnVertically(PlayerBox, EnvironmentBox))
            {
                m_Player->resetVelocity();
                if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                {
                    m_Player->onPlatform();
                }
            }
            else if (isCollidingLeft(PlayerBox, EnvironmentBox))
            {
                // std::cout << "End Pipe Working!" << std::endl;
            }
            resolveCollisions(PlayerBox, EnvironmentBox);
            m_Player->setPosition(PlayerBox.getPosition());
            m_EndPipes[i]->m_Position = EnvironmentBox.getPosition();
        }
    }
    
}
void Level::resolveInteractiveEnvironmentCollisions()
{
    for (int i = 0; i < m_EnvironmentInteractive.size(); i++)
    {
            AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
            AABBox EnvironmentBox = AABBox(m_EnvironmentInteractive[i]->m_Position, m_EnvironmentInteractive[i]->getSize());
            EnvironmentBox.setFixed(true);
            if (isColliding(PlayerBox, EnvironmentBox))
            {
                if (isCollidingOnVertically(PlayerBox, EnvironmentBox))
                {
                    m_Player->resetVelocity();
                    if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                    {
                        m_Player->onPlatform();
                    }
                    if (isCollidingOnBottom(PlayerBox, EnvironmentBox))
                    {
                        m_EnvironmentInteractive[i]->onNotify();
                    }
                }
                resolveCollisions(PlayerBox, EnvironmentBox);
                m_Player->setPosition(PlayerBox.getPosition());
                m_EnvironmentInteractive[i]->m_Position = EnvironmentBox.getPosition();
                
            }
    }
}
void Level::applyBoundaries()
{
    if (isInHole())
    {
        // std::cout << "In Hole" << std::endl;
    }
    else if (m_Player->GetPosition().y > m_Ground->m_Position.y - m_Player->GetSize().y)
    {
        m_Player->setPosition(Vector2{m_Player->GetPosition().x, m_Ground->m_Position.y - m_Player->GetSize().y});
        m_Player->resetVelocity();
        m_Player->onPlatform();
    }
}
void Level::render()
{
    float Offset = 900;
    // printf("Rendering Level\n");
    switch (m_WorldType)
    {
        case Level::WorldType::OVERWORLD:
        {
            // printf("Overworld\n");
            ClearBackground(Color{105, 147, 245, 255});
            break;
        }
        case Level::WorldType::UNDERGROUND:
        {
            ClearBackground(BLACK);
            break;
        }
    }
    Camera2D camera = { 0 };
    Vector2 target = m_CameraPosition;
    camera.target = target;
    
    float CurrentHeight = GetScreenHeight();
    float CurrentWidth = GetScreenWidth();
    float Zoom;
    // std::cout << "Current Height: " << CurrentHeight << std::endl;
    // std::cout << "Current Width: " << CurrentWidth << std::endl;
    // std::cout << m_ScreenSize.x << ", " << m_ScreenSize.y << std::endl;
    if (CurrentWidth / CurrentHeight < (m_ScreenSize.x / m_ScreenSize.y))
    {
        // std::cout << "Width based" << std::endl;
        Zoom = CurrentWidth / m_ScreenSize.x;
    }
    else
    {
        // std::cout << "Height based" << std::endl;
        Zoom = CurrentHeight / m_ScreenSize.y;
    }
    // std::cout << "Zoom: " << Zoom << std::endl;
    Zoom /= 2;
    camera.offset = {0, Offset * (Zoom)};
    camera.zoom = Zoom;
    BeginMode2D(camera);
    for (auto& object : m_Environment)
    {
        object->render();
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        object->render();
    }
    for (auto& object : m_Drawables)
    {
        object->render();
    }
    Ground::GetGround()->render();
    for (auto& object : m_Lifts)
    {
        object->render();
    }
    m_Player->Draw();
    for (auto& object : m_EndPipes)
    {
        object->render();
    }
    float HidePositionX = m_ScreenSize.x * 2;
    DrawRectangle((HidePositionX) + m_CameraPosition.x, -Offset, INT_MAX, INT_MAX, RED);
    EndMode2D();
    // DrawRectangle(HidePositionX + m_CameraPosition.x, 0, CurrentWidth - HidePositionX / Zoom, CurrentHeight, BLACK);
    // std::cout << m_CameraPosition.x << std::endl;
    
}
unsigned int Level::update(float DeltaTime)
{
    m_Ground->update(m_CameraPosition);
    unsigned int ReturnResult = doPauseLogic();
    if (ReturnResult != LEVEL_RETURN_MESSAGE::RUNNING)
    {
        return ReturnResult;
    }
    isPlayerFinished = isInHole();
    float accX = 0;
    if (!isPlayerFinished) {
		m_Player->control(accX,true);
    }
	else m_Player->control(accX, false);
    m_Player->accelerate(Vector2{ accX, 9.81f }, DeltaTime);
    m_Player->Update(DeltaTime);
    if (m_Player->GetPosition().x > m_CameraPosition.x + m_PlayerOffset)
    {
        m_CameraPosition.x = m_Player->GetPosition().x - m_PlayerOffset;
    }
    if (m_Player->GetPosition().x < m_CameraPosition.x)
    {
        Vector2 NewPosition = {m_CameraPosition.x, m_Player->GetPosition().y};
        m_Player->setPosition(NewPosition);
    }
    for (auto& object : m_Environment)
    {
        object->update();
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        object->update();
    }
    for (auto& object : m_Lifts)
    {
        object->update(DeltaTime);
    }
    applyBoundaries();
    resolveEnvironmentCollisions();
    resolveInteractiveEnvironmentCollisions();
    return LEVEL_RETURN_MESSAGE::RUNNING;
}
bool Level::isInHole()
{
    for (int i = 0; i < m_Ground -> getHoleCount(); i++)
    {
        auto hole = m_Ground -> getHole(i);
        if (m_Player->GetPosition().x > hole.first)
        {
            // std::cout << "BIGGER THAN HOLE" << std::endl;
            // std::cout << "Hole: " << hole.first << ", " << hole.second << std::endl;
            if (m_Player->GetPosition().x + m_Player -> GetSize().x < hole.first + hole.second * 100)
            {
                // std::cout << "SMALLER THAN HOLE" << std::endl;
                if (m_Player->GetPosition().y + m_Player -> GetSize().y > m_Ground->m_Position.y)
                {
                    // std::cout << "LOWER THAN HOLE" << std::endl;
                    return true;
                }
            }
        }
    }
    return false;
}
void Level::pauseLevel()
{
    m_Paused = true;
}
void Level::continueLevel()
{
    m_Paused = false;
}
unsigned int Level::doPauseLogic()
{
    if (IsKeyPressed(KEY_P))
    {
        if (m_Paused)
        {
            continueLevel();
            return LEVEL_RETURN_MESSAGE::CONTINUE;
        }
        else
        {
            pauseLevel();
            return LEVEL_RETURN_MESSAGE::PAUSE;
        }
    }
    if (m_Paused)
    {
        if (IsKeyPressed(KEY_Q))
        {
            return LEVEL_RETURN_MESSAGE::QUIT;
        }
    }
    return LEVEL_RETURN_MESSAGE::RUNNING;
}

Level101::Level101()
{
    load();
}
Level101::~Level101()
{
}
void Level101::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_101);
}
unsigned int Level101::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void Level101::render()
{
    Level::render();
}
Level101* Level101::GetLevel101()
{
    static Level101 level;
    return &level;
}
LevelTesting::LevelTesting()
{
    load();
}
LevelTesting::~LevelTesting()
{
}
void LevelTesting::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_TESTING);
}
unsigned int LevelTesting::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void LevelTesting::render()
{
    Level::render();
}
LevelTesting* LevelTesting::GetLevelTesting()
{
    static LevelTesting level;
    return &level;
}
Level103::Level103()
{
    load();
}
Level103::~Level103()
{
}
Level103* Level103::GetLevel103()
{
    static Level103 level;
    return &level;
}
void Level103::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_103);
}