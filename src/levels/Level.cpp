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
    Camera2D camera = { 0 };
    Vector2 target = m_CameraPosition;
    camera.target = target;
    camera.offset = {0, 0};
    camera.zoom = 1.0f;
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
    Ground::GetGround()->render(m_CameraPosition);
    m_Player->Draw();
    EndMode2D();
}
void Level::update(float DeltaTime)
{
    isPlayerFinished = isInHole();
    if (!isPlayerFinished) m_Player -> Update(DeltaTime);
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

Level101::Level101()
{
    load();
}
Level101::~Level101()
{
}
void Level101::load()
{
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE, Vector2{2300, m_Ground->m_Position.y - 135}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE, Vector2{3100, m_Ground->m_Position.y - 175}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE, Vector2{3700, m_Ground->m_Position.y - 195}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::BRICK, Vector2{1500, 300}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::BRICK, Vector2{1700, 300}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::BRICK, Vector2{1900, 300}));
    m_EnvironmentInteractive.push_back(EnvironmentInteractiveObjectFactory::GetEnvironmentInteractiveFactory().CreateEnvironmentInteractiveObject(EnvironmentInteractiveObjectFactory::EnvironmentInteractiveObjectType::QUESTION_BLOCK, Vector2{1600, 300}));
    m_EnvironmentInteractive.push_back(EnvironmentInteractiveObjectFactory::GetEnvironmentInteractiveFactory().CreateEnvironmentInteractiveObject(EnvironmentInteractiveObjectFactory::EnvironmentInteractiveObjectType::QUESTION_BLOCK, Vector2{1800, 300}));

    m_Ground->addHole(5300, 2);
    m_Ground->addHole(6900, 3);
    m_Drawables.push_back(DrawableObjectFactory::GetDrawableObjectFactory().CreateDrawableObject(DrawableObjectFactory::DrawableObjectType::CLOUD, Vector2{700, 100}));

}
void Level101::update(float DeltaTime)
{
    Level::update(DeltaTime);
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