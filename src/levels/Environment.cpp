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
        case 0:
            return Ground::GetGround();
            break;
        case 1:
        {
            std::cout << "Creating Warp Pipe at " << Position.x << ", " << Position.y << std::endl;
            WarpPipe* pipe = new WarpPipe(Position, Vector2{208, 195});
            return pipe;
        }
        case 2:
        {
            Brick* brick = new Brick(Position, Vector2{100, 100});
            return brick;
        }
        break;
        
    }
}
Ground::Ground() : EnvironmentObject(Vector2{0, 746}, Vector2{1024, 200})
{
    m_Texture = LoadTexture("assets/textures/ground.png");
}
Ground::~Ground()
{
}
EnvironmentObject* Ground::GetGround()
{
    static Ground ground;
    return &ground;
}
void Ground::render()
{
    DrawTexture(m_Texture, m_Position.x, m_Position.y, WHITE);
}
void Ground::update()
{
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
WarpPipe::WarpPipe(Vector2 Position, Vector2 Size) : EnvironmentObject(Position, Size)
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




