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
}
Level::~Level()
{
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
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::BRICK, Vector2{500, 300}));
    m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::GROUND, Vector2{0, 746}));
}
void Level101::update()
{
    // checkEnvironmentCollisions();
    // resolveEnvironmentCollisions();
}
void Level101::render()
{
    for (auto& object : m_Environment)
    {
        object->render();
    }
}
Level101* Level101::GetLevel101()
{
    static Level101 level;
    return &level;
}