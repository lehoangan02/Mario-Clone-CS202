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

    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::BRICK, Vector2{500, 300}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::GROUND, Vector2{0, 746}));
}
void Level101::update(float DeltaTime)
{
    m_Player -> Update(DeltaTime);
    // std::cout << "Player position: " << m_Player->GetPosition().x << ", " << m_Player->GetPosition().y << std::endl;
    // std::cout << "Camera position: " << m_CameraPosition.x << ", " << m_CameraPosition.y << std::endl;
    if (m_Player->GetPosition().x > m_CameraPosition.x + m_PlayerOffset)
    {
        m_CameraPosition.x = m_Player->GetPosition().x - m_PlayerOffset;
    }
    if (m_Player->GetPosition().x < m_CameraPosition.x)
    {
        // m_Player->SetPosition({m_CameraPosition.x, m_Player->GetPosition().y});
    }
    // checkEnvironmentCollisions();
    // resolveEnvironmentCollisions();
}
void Level101::render()
{
    Camera2D camera = { 0 };
    Vector2 target = m_CameraPosition;
    // target = {0, 0};
    camera.target = target;
    camera.offset = (Vector2){0, 0};
    camera.zoom = 1.0f;
    BeginMode2D(camera);
    for (auto& object : m_Environment)
    {
        object->render();
    }
    m_Player->Draw();
    EndMode2D();
}
Level101* Level101::GetLevel101()
{
    static Level101 level;
    return &level;
}