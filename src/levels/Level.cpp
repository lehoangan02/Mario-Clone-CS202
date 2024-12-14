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
    for (auto& object : m_Environment)
    {
        delete object;
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        delete object.first;
        delete object.second;
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
    m_Player->setPosition(m_StartPosition);
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
            if (isCollidingOnVertically(PlayerBox, EnvironmentBox))
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
        Item* CurrentItem = m_EnvironmentInteractive[i].second;
        if (!CurrentItem) continue;
        if (IsKeyPressed(KEY_E))
        {
            CurrentItem->onNotify();
        }
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
                    CurrentItem->onNotify();
                    if (CurrentItem->getItemID() == Itemtype::MUSHROOM)
                    {
                        std::cout << "Mushroom" << std::endl;
                    }
                    
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
    if (isPlayerInHole())
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
void Level::handleItemLogic()
{
    for (int i = 0; i < m_EnvironmentInteractive.size(); i++)
    {
        Item* CurrentItem = m_EnvironmentInteractive[i].second;
        if (!CurrentItem) continue;
        if (CurrentItem -> getItemID() == Itemtype::MUSHROOM)
        {
            AABBox ItemBox = AABBox(CurrentItem->GetPosition(), CurrentItem->GetSize());
            if (m_Ground->isInHole(ItemBox)) continue;
            Mushroom* MushroomItem = dynamic_cast<Mushroom*>(CurrentItem);
            // std::cout << "Mushroom position: " << MushroomItem->GetPosition().y << std::endl;
            if (MushroomItem->GetPosition().y > m_Ground->m_Position.y - MushroomItem->GetSize().y)
            {
                // std::cout << "Mushroom is on the ground" << std::endl;
                MushroomItem->setPosition(MushroomItem->GetPosition().x, m_Ground->m_Position.y - MushroomItem->GetSize().y);
                MushroomItem->ResetYVelocity();
            }
        }
    }
    for (int i = 0; i < m_EnvironmentInteractive.size(); i++)
    {
        Item* CurrentItem = m_EnvironmentInteractive[i].second;
        if (!CurrentItem) continue;
        if (CurrentItem->getItemID() == Itemtype::MUSHROOM)
        {
            Mushroom* MushroomItem = dynamic_cast<Mushroom*>(CurrentItem);
            // if (IsKeyPressed(KEY_F))
            // {
            //     std::cout << "Trying to flip" << std::endl;
            //     MushroomItem->FlipDirection();
            // }
            if (MushroomItem->isFinishSpawning())
            {
                MushroomItem->Accelerate(GetFrameTime());
            }
            for (int j = 0; j < m_EnvironmentInteractive.size(); ++j)
            {
                AABBox ItemBox = AABBox(MushroomItem->GetPosition(), MushroomItem->GetSize());
                AABBox EnvironmentBox = AABBox(m_EnvironmentInteractive[j].first->m_Position, m_EnvironmentInteractive[j].first->getSize());
                EnvironmentBox.setFixed(true);
                if (isCollidingOnVertically(ItemBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(ItemBox, EnvironmentBox, 10.0f)))
                {
                    if (isCollidingOnBottom(ItemBox, EnvironmentBox))
                    {
                        MushroomItem->ResetYVelocity();
                    }
                    else if (isCollidingOnTop(ItemBox, EnvironmentBox))
                    {
                        MushroomItem->ResetYVelocity();
                    }
                }
                else if (isCollidingHorizontally(ItemBox, EnvironmentBox))
                {
                    MushroomItem->FlipDirection();
                }
                resolveCollisions(ItemBox, EnvironmentBox);
                MushroomItem->setPosition(ItemBox.getPosition().x, ItemBox.getPosition().y);
                // m_EnvironmentInteractive[i].first->m_Position = EnvironmentBox.getPosition();
            }
        }
    }
    for (int i = 0; i < m_EnvironmentInteractive.size(); i++)
    {
        Item* CurrentItem = m_EnvironmentInteractive[i].second;
        if (CurrentItem->getItemID() == Itemtype::MUSHROOM)
        {
            Mushroom* MushroomItem = dynamic_cast<Mushroom*>(CurrentItem);
            if (IsKeyPressed(KEY_F))
            {
                std::cout << "Trying to flip" << std::endl;
                MushroomItem->FlipDirection();
            }
            if (MushroomItem->isFinishSpawning())
            {
                MushroomItem->Accelerate(GetFrameTime());
            }
            else
            {
                continue;
            }
            for (int j = 0; j < m_Environment.size(); j++)
            {
                // std::cout << "j: " << j << std::endl;
                AABBox ItemBox = AABBox(MushroomItem->GetPosition(), MushroomItem->GetSize());
                AABBox EnvironmentBox = AABBox(m_Environment[j]->m_Position, m_Environment[j]->getSize());
                EnvironmentBox.setFixed(true);
                if (isCollidingOnVertically(ItemBox, EnvironmentBox) && !(isCollidingHorizontallyRawLess(ItemBox, EnvironmentBox, 10.0f)))
                {
                    if (isCollidingOnBottom(ItemBox, EnvironmentBox))
                    {
                        MushroomItem->ResetYVelocity();
                    }
                    else if (isCollidingOnTop(ItemBox, EnvironmentBox))
                    {
                        MushroomItem->ResetYVelocity();
                    }
                }
                else if (isCollidingHorizontally(ItemBox, EnvironmentBox))
                {
                    MushroomItem->FlipDirection();
                }
                resolveCollisions(ItemBox, EnvironmentBox);
                MushroomItem->setPosition(ItemBox.getPosition().x, ItemBox.getPosition().y);
                m_Environment[j]->m_Position = EnvironmentBox.getPosition();
            }
        }
    }
}
void Level::render()
{
    float Offset = 900;
    switch (m_Ground -> m_WorldType)
    {
        case Level::WorldType::OVERWORLD:
        {
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
    target.x = roundf(target.x);
    target.y = roundf(target.y);
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
    m_Background.render();
    if (m_FlagPole != nullptr)
    {
        m_FlagPole -> render();
    }
    for (auto& object : m_Environment)
    {
        if (object->getType() == EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE)
        {
            // std::cout << "Warp Pipe at: " << object->m_Position.x << " " << object->m_Position.y << std::endl;
        }
        object->render();
    }
    for (auto& object : m_Drawables)
    {
        object->render();
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        if (object.second == nullptr) continue;
        object.second->Draw();
        if (object.second->getItemID() == Itemtype::MUSHROOM)
        {
            Mushroom* MushroomItem = dynamic_cast<Mushroom*>(object.second);
            DrawBoundingBox(MushroomItem->GetPosition(), MushroomItem->GetSize(), RED);
        }
    }
    for (auto& object : m_EnvironmentInteractive)
    {
        object.first->render();
    }
    
    Ground::GetGround()->render();
    for (auto& object : m_Lifts)
    {
        object->render();
    }
    goomba->render();
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
    if (IsKeyPressed(KEY_O))
    {
        m_TouchedFlag = true;
    }
    if (m_Paused)
    {
        return;
    }
    isPlayerFinished = isPlayerInHole();
	if (isPlayerFinished)
	{
		InHole control(m_Player);
		control.execute(DeltaTime);
	}
    else if (!isPlayerFinished && m_InControl && !m_TouchedFlag)
    {
		FullControl control(m_Player);
        control.execute(DeltaTime);
    }
    else if (!isPlayerFinished && m_TouchedFlag)
    {
        Command *control = AutoMove::getInstance(m_Player);
        control->execute(DeltaTime);
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
    if (m_Ground->m_WorldType == Level::WorldType::OVERWORLD)
    {
        m_Background.update(m_CameraPosition, true);
    }
    else
    {
        m_Background.update(m_CameraPosition, false);
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
    goomba->update(DeltaTime);
    if (m_FlagPole != nullptr)
    {
        m_FlagPole -> update();
    }
    applyBoundaries();
    resolveEnvironmentCollisions();
    resolveInteractiveEnvironmentCollisions();
    handleItemLogic();
    resolveFlagPoleCollisions();
}
bool Level::isPlayerInHole()
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
    if (m_Player->isSliding())
    {

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
Level::Background::Background()
{
    m_TextureLayer1 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/cloud_lonely.png");
    m_TextureLayer2 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/clouds_mg_1_lightened.png");
    m_TextureLayer3 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/glacial_mountains_lightened.png");
    m_TextureLayer4 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/clouds_bg.png");
    // m_TextureLayer5 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/Background5.png");
    // m_TextureLayer6 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/Background6.png");
    // m_TextureLayer7 = LoadTexture("assets/textures/Glacial-mountains-parallax-background_vnitti/Layers/Background7.png");

    m_TextureLayer8 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0000_9.png");
    m_TextureLayer9 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0001_8.png");
    m_TextureLayer10 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0003_6.png");
    m_TextureLayer11 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0005_5.png");
    m_TextureLayer12 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0006_4.png");
    m_TextureLayer13 = LoadTexture("assets/textures/Free Pixel Art Forest/PNG/Background layers/Layer_0009_2.png");

}
void Level::Background::update(Vector2 CameraPosition, bool Overworld)
{
    m_Overworld = Overworld;
    Vector2 Move = Vector2Subtract(CameraPosition, m_PreviousCameraPosition);
    m_PreviousCameraPosition = CameraPosition;
    m_Layer1Position = Vector2Add(m_Layer1Position, Vector2Scale(Move, 0.95));
    m_Layer2Position = Vector2Add(m_Layer2Position, Vector2Scale(Move, 0.96));
    m_Layer3Position = Vector2Add(m_Layer3Position, Vector2Scale(Move, 0.98));
    m_Layer4Position = Vector2Add(m_Layer4Position, Vector2Scale(Move, 0.97));

    m_Layer8Position = Vector2Add(m_Layer8Position, Vector2Scale(Move, 0.95));
    m_Layer9Position = Vector2Add(m_Layer9Position, Vector2Scale(Move, 0.96));
    m_Layer10Position = Vector2Add(m_Layer10Position, Vector2Scale(Move, 0.98));
    m_Layer11Position = Vector2Add(m_Layer11Position, Vector2Scale(Move, 0.97));
    m_Layer12Position = Vector2Add(m_Layer12Position, Vector2Scale(Move, 0.95));
    m_Layer13Position = Vector2Add(m_Layer13Position, Vector2Scale(Move, 0.96));


}
void Level::Background::render()
{
    // std::cout << "Layer2 Pos: " << m_Layer2Position.x << " " << m_Layer2Position.y << std::endl;
    if (m_Overworld)
    {
        DrawTextureEx(m_TextureLayer4, m_Layer4Position, 0, 9, WHITE);
        DrawTextureEx(m_TextureLayer3, m_Layer1Position, 0, 9, WHITE);
        DrawTextureEx(m_TextureLayer2, m_Layer2Position, 0, 9, WHITE);
        DrawTextureEx(m_TextureLayer1, m_Layer3Position, 0, 9, WHITE);
    }
    else
    {
        DrawTextureEx(m_TextureLayer13, m_Layer13Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer12, m_Layer12Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer8, m_Layer8Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer9, m_Layer9Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer10, m_Layer10Position, 0, 7, WHITE);
        DrawTextureEx(m_TextureLayer11, m_Layer11Position, 0, 7, WHITE);
        
        
    }
    
}
void Level::resolveFlagPoleCollisions()
{
    if (m_FlagPole == nullptr) return;
    static bool PullDone = false;
    AABBox PlayerBox = AABBox(m_Player->GetPosition(), m_Player->GetSize());
    AABBox EnvironmentBox = AABBox(m_FlagPole -> m_Position, m_FlagPole -> getSize());
    // std::cout << "Flag Pole Position: " << m_FlagPole.m_Position.x << " " << m_FlagPole.m_Position.y << std::endl;
    // std::cout << "Flag Pole Size: " << m_FlagPole.getSize().x << " " << m_FlagPole.getSize().y << std::endl;
    EnvironmentBox.setFixed(true);
    if (!m_TouchedFlag && isColliding(PlayerBox, EnvironmentBox))
    {
        // std::cout << "Colliding with flag pole" << std::endl;
        resolveCollisions(PlayerBox, EnvironmentBox);
        m_TouchedFlag = true;
        m_Player->setPosition(PlayerBox.getPosition());
        m_FlagPole -> m_Position = EnvironmentBox.getPosition();
        m_FlagPole -> notifyPull();
    }
    PullDone = m_FlagPole -> isDone();
    if (PullDone)
    {
        DrawText("Level Complete", 100, 100, 20, RED);
    }
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
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_TESTING);
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
    m_LevelID = LevelFactory::LEVEL_103;
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
void Level103::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void Level103::render()
{
    Level::render();
}
HiddenLevel101::HiddenLevel101()
{
    m_LevelID = LevelFactory::HIDDEN_LEVEL_101;
    load();
}
HiddenLevel101::~HiddenLevel101()
{
}
HiddenLevel101* HiddenLevel101::GetHiddenLevel101()
{
    static HiddenLevel101 level;
    return &level;
}
void HiddenLevel101::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::HIDDEN_LEVEL_101);
}
void HiddenLevel101::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void HiddenLevel101::render()
{
    Level::render();
}
Level102::Level102()
{
    m_LevelID = LevelFactory::LEVEL_102;
    load();
}
Level102::~Level102()
{
}
Level102* Level102::GetLevel102()
{
    static Level102 level;
    return &level;
}
void Level102::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::LEVEL_102);
}
void Level102::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void Level102::render()
{
    Level::render();
}
HiddenLevel102::HiddenLevel102()
{
    m_LevelID = LevelFactory::HIDDEN_LEVEL_102;
    load();
}
HiddenLevel102::~HiddenLevel102()
{
}
HiddenLevel102* HiddenLevel102::GetHiddenLevel102()
{
    static HiddenLevel102 level;
    return &level;
}
void HiddenLevel102::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::HIDDEN_LEVEL_102);
}
void HiddenLevel102::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void HiddenLevel102::render()
{
    Level::render();
}
HiddenLevel103::HiddenLevel103()
{
    m_LevelID = LevelFactory::HIDDEN_LEVEL_103;
    load();
}
HiddenLevel103::~HiddenLevel103()
{
}
HiddenLevel103* HiddenLevel103::GetHiddenLevel103()
{
    static HiddenLevel103 level;
    return &level;
}
void HiddenLevel103::load()
{
    MapLoader::GetMapLoader().LoadMap(this, LevelFactory::LevelType::HIDDEN_LEVEL_103);
}
void HiddenLevel103::update(float DeltaTime)
{
    return Level::update(DeltaTime);
}
void HiddenLevel103::render()
{
    Level::render();
}