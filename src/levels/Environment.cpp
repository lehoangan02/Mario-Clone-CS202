#include "Environment.hpp"
EnvironmentObjectFactory& EnvironmentObjectFactory::GetEnvironmentFactory()
{
    static EnvironmentObjectFactory Factory;
    return Factory;
}
EnvironmentObject* EnvironmentObjectFactory::CreateEnvironmentObject(int Type, Vector2 Position)
{
    switch (Type)
    {
        case EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE:
        {
            std::cout << "Creating Warp Pipe at " << Position.x << ", " << Position.y << std::endl;
            WarpPipe* pipe = new WarpPipe(Position);
            return pipe;
        }
        case EnvironmentObjectFactory::EnvironmentObjectType::BRICK:
        {
            Brick* brick = new Brick(Position, Vector2{100, 100});
            return brick;
        }
        break;
    }
}
Ground::Ground() : m_Position(Vector2{0, 746}), m_Size(Vector2{100, 100})
{
    m_Texture = LoadTexture("assets/textures/ground1x1.png");
}
Ground::~Ground()
{
}
Ground* Ground::GetGround()
{
    static Ground ground;
    return &ground;
}
void Ground::render(Vector2 CameraPosition)
{
    // std::cout << "Camera Position: " << CameraPosition.x << ", " << CameraPosition.y << std::endl;
    // std::cout << "Size: " << m_Size.x << ", " << m_Size.y << std::endl;
    int PositionX = static_cast<int>(CameraPosition.x / m_Size.x);
    // std::cout << "PositionX: " << PositionX << std::endl;
    for (int i = 0; i < 20; ++i)
    {
        DrawTexture(m_Texture, i * m_Size.x + m_Size.x * PositionX , m_Position.y, WHITE);
        DrawTexture(m_Texture, i * m_Size.x + m_Size.x * PositionX , m_Position.y + m_Size.y, WHITE);
    }

    for (auto& hole : m_Holes)
    {
        int Width = hole.second * 100;

        DrawRectangle(hole.first, m_Position.y, Width, 200, Color{105, 147, 245, 255});
    }
}
void Ground::update()
{

}
void Ground::addHole(float x, unsigned int y)
{
    m_Holes.push_back(std::make_pair(x, y));
}
WarpPipeTextureFlyWeight::WarpPipeTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/pipe.png");
}
WarpPipeTextureFlyWeight::~WarpPipeTextureFlyWeight()
{
}
WarpPipeTextureFlyWeight* WarpPipeTextureFlyWeight::GetWarpPipeTextureFlyweight()
{
    static WarpPipeTextureFlyWeight texture;
    return &texture;
}
void WarpPipeTextureFlyWeight::render(Vector2 Position)
{
    DrawTexture(m_Texture, Position.x, Position.y, WHITE);
}
WarpPipe::WarpPipe(Vector2 Position) : EnvironmentObject(Position, Vector2{209, 195})
{
}
WarpPipe::~WarpPipe()
{
}
void WarpPipe::render()
{
    WarpPipeTextureFlyWeight::GetWarpPipeTextureFlyweight()->render(m_Position);
}
void WarpPipe::update()
{
}
BrickTextureFlyWeight::BrickTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/brick.png");
}
BrickTextureFlyWeight::~BrickTextureFlyWeight()
{
}
BrickTextureFlyWeight* BrickTextureFlyWeight::GetBrickTextureFlyWeight()
{
    static BrickTextureFlyWeight texture;
    return &texture;
}
void BrickTextureFlyWeight::render(Vector2 Position)
{
    DrawTexture(m_Texture, Position.x, Position.y, WHITE);
}
Brick::Brick(Vector2 Position, Vector2 Size) : EnvironmentObject(Position, Size)
{
}
Brick::~Brick()
{
}
void Brick::render()
{
    BrickTextureFlyWeight::GetBrickTextureFlyWeight()->render(m_Position);
}
void Brick::update()
{
}




