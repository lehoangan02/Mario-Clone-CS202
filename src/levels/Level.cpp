#include "Level.hpp"
LevelFactory& LevelFactory::GetLevelFactory()
{
    static LevelFactory Factory;
    return Factory;
}
Level* LevelFactory::CreateLevel(int Type)
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
    

}
void Level::attachPlayer(Character* Player)
{
    m_Player = Player;
    m_EndPipeHandler.attachPlayer(Player);
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
            if (isCollidingOnVertically(PlayerBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(PlayerBox, EnvironmentBox, 20.0f)))
            {
                if (isCollidingOnBottom(PlayerBox, EnvironmentBox))
                {
                    m_Player->resetVelocity();
                }
                else if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                {
                    m_Player->resetVelocity();
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
}
void Level::resolveInteractiveEnvironmentCollisions()
{
    for (int i = 0; i < m_EnvironmentInteractive.size(); i++)
    {
            AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
            AABBox EnvironmentBox = AABBox(m_EnvironmentInteractive[i].first->m_Position, m_EnvironmentInteractive[i].first->getSize());
            EnvironmentBox.setFixed(true);
            if (isColliding(PlayerBox, EnvironmentBox))
            {
                if (isCollidingOnVertically(PlayerBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(PlayerBox, EnvironmentBox, 15.0f)))
                {
                    m_Player->resetVelocity();
                    if (isCollidingOnTop(PlayerBox, EnvironmentBox))
                    {
                        m_Player->onPlatform();
                    }
                    else if (isCollidingOnBottom(PlayerBox, EnvironmentBox))
                    {
                        m_EnvironmentInteractive[i].first->onNotify();                        
                        m_EnvironmentInteractive[i].second->onNotify();
                    }
                }
                resolveCollisions(PlayerBox, EnvironmentBox);
                m_Player->setPosition(PlayerBox.getPosition());
                m_EnvironmentInteractive[i].first->m_Position = EnvironmentBox.getPosition();
                
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
    switch (m_Ground -> m_WorldType)
    {
        case Level::WorldType::OVERWORLD:
        {
            // printf("Overworld\n");
            ClearBackground(Color{105, 147, 245, 255});
            break;
        }
        case Level::WorldType::UNDERGROUND:
        {
            // printf("Underground\n");
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
        object.first->render();
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        object.second->Draw();
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
    
}
void Level::update(float DeltaTime)
{
    m_Ground->update(m_CameraPosition);
    doPauseLogic();
    if (m_Paused)
    {
        return;
    }
    isPlayerFinished = isInHole();
	if (!isPlayerFinished)
	{
        FullControl control(m_Player);
        control.execute(DeltaTime);
	}
    else {
		InHole control(m_Player);
		control.execute(DeltaTime);
    }
    if (m_Player->GetPosition().x > m_CameraPosition.x + m_PlayerOffset)
    {
        float Delta = m_Player->GetPosition().x - m_CameraPosition.x - m_PlayerOffset;
        m_CameraPosition.x += Delta * 0.05;
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
        object.first ->update();
    }
    for (auto& object : m_EnvironmentInteractive)
    {        object.second ->Update(DeltaTime);
    }
    for (auto& object : m_Lifts)
    {
        object->update(DeltaTime);
    }
    if (m_EndPipeHandler.update())
    {
        return;
    }
    applyBoundaries();
    resolveEnvironmentCollisions();
    resolveInteractiveEnvironmentCollisions();
}
bool Level::isInHole()
{
    for (int i = 0; i < m_Ground -> getHoleCount(); i++)
    {
        auto hole = m_Ground -> getHole(i);
        if (m_Player->GetPosition().x > hole.first)
        {
            if (m_Player->GetPosition().x + m_Player -> GetSize().x < hole.first + hole.second * 100)
            {
                if (m_Player->GetPosition().y + m_Player -> GetSize().y > m_Ground->m_Position.y)
                {
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
void Level::EndPipeHandler::addEndPipe(EndPipe* Pipe)
{
    m_EndPipes.push_back(Pipe);
}
void Level::EndPipeHandler::attachPlayer(Character* Player)
{
    m_Player = Player;
}
bool Level::EndPipeHandler::update()
{
    if (inPipe)
    {
        // if (slidePipeComplete)
        // return true;
    }
    for (int i = 0; i < m_EndPipes.size(); ++i)
    {
        AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
        AABBox EnvironmentBox = AABBox(m_EndPipes[i]->m_Position, m_EndPipes[i]->getSize());
        EnvironmentBox.setFixed(true);
        if (isColliding(PlayerBox, EnvironmentBox))
        {
            if (isCollidingLeft(PlayerBox, EnvironmentBox))
            {
                m_Player ->SlidePipe(slidingDirection::right);
                inPipe = true;
            }
            else
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
                m_EndPipes[i]->m_Position = EnvironmentBox.getPosition();
            }
        }
    }
    return false;
}

Level101::Level101()
{
    m_LevelID = LevelFactory::LEVEL_101;
    load();
}
Level101::~Level101()
{
}
void Level101::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_101);
}
void Level101::update(float DeltaTime)
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
    m_LevelID = LevelFactory::LEVEL_TESTING;
    load();
}
LevelTesting::~LevelTesting()
{
}
void LevelTesting::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_101);
}
void LevelTesting::update(float DeltaTime)
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