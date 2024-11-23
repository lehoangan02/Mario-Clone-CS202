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
void Level::applyBoundaries()
{
    if (m_Player->GetPosition().y > m_Ground->m_Position.y - m_Player->GetSize().y)
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
    camera.offset = (Vector2){0, 0};
    camera.zoom = 1.0f;
    BeginMode2D(camera);
    for (auto& object : m_Environment)
    {
        object->render();
    }
    Ground::GetGround()->render(m_CameraPosition);
    m_Player->Draw();
    EndMode2D();
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
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE, Vector2{600, 600}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE, Vector2{1200, 600}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE, Vector2{1500, 600}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::BRICK, Vector2{2000, 500}));
    m_Ground->addHole(1200, 2);
    m_Ground->addHole(300, 3);
}
void Level101::update(float DeltaTime)
{
    m_Player -> Update(DeltaTime);
    if (m_Player->GetPosition().x > m_CameraPosition.x + m_PlayerOffset)
    {
        m_CameraPosition.x = m_Player->GetPosition().x - m_PlayerOffset;
    }
    if (m_Player->GetPosition().x < m_CameraPosition.x)
    {
        Vector2 NewPosition = {m_CameraPosition.x, m_Player->GetPosition().y};
        m_Player->setPosition(NewPosition);
    }
    applyBoundaries();
    // checkEnvironmentCollisions();
    resolveEnvironmentCollisions();
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