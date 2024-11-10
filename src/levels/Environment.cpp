#include "Environment.hpp"
EnvironmentObjectFactory& EnvironmentObjectFactory::GetEnvironmentFactory()
{
    static EnvironmentObjectFactory Factory;
    return Factory;
}
EnvironmentObject& EnvironmentObjectFactory::CreateEnvironmentObject(int Type)
{
    switch (Type)
    {

    }
}
Ground::Ground() : EnvironmentObject(Vector2{0, 746}, Vector2{1024, 200})
{
    m_Texture = LoadTexture("assets/textures/ground.png");
}
Ground::~Ground()
{
}
EnvironmentObject& Ground::GetGround()
{
    static Ground ground;
    return ground;
}
void Ground::render()
{
    DrawTexture(m_Texture, m_Position.x, m_Position.y, WHITE);
}
void Ground::update()
{

}
