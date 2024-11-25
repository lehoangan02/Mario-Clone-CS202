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
            // std::cout << "Current Position: " << pipe->m_Position.x << ", " << pipe->m_Position.y << std::endl;
            return pipe;
        }
        case EnvironmentObjectFactory::EnvironmentObjectType::BRICK:
        {
            Brick* brick = new Brick(Position);
            return brick;
        }
        break;
        default:
        {
            std::cerr << "Invalid Environment Object Type\n";
            return nullptr;
        }
    }
}
EnvironmentInteractiveObjectFactory& EnvironmentInteractiveObjectFactory::GetEnvironmentInteractiveFactory()
{
    static EnvironmentInteractiveObjectFactory Factory;
    return Factory;
}
EnvironmentObjectInteractive* EnvironmentInteractiveObjectFactory::CreateEnvironmentInteractiveObject(int Type, Vector2 Position)
{
    switch (Type)
    {
        case EnvironmentInteractiveObjectFactory::EnvironmentInteractiveObjectType::QUESTION_BLOCK:
        {
            QuestionBlock* block = new QuestionBlock(Position);
            return block;
        }
        break;
        default:
        {
            std::cerr << "Invalid Environment Interactive Object Type\n";
            return nullptr;
        }
    }
}
void EnvironmentObjectInteractive::move(Vector2 Position)
{
    // std::cout << "Moving Object x: " << Position.x << ", y: " << Position.y << std::endl;
    m_Position = {m_Position.x + Position.x, m_Position.y + Position.y};
    // std::cout << "New Position x: " << m_Position.x << ", y: " << m_Position.y << std::endl;
}
Ground::Ground() : MapObject((Vector2{0, 618}), (Vector2{100, 100}))
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
    // std::cout << "Rendering Warp Pipe at " << m_Position.x << ", " << m_Position.y << std::endl;
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
Brick::Brick(Vector2 Position) : EnvironmentObject(Position, Vector2{100, 100})
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

QuestionBlockTextureFlyWeight::QuestionBlockTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/question_block.png");
}
QuestionBlockTextureFlyWeight::~QuestionBlockTextureFlyWeight()
{
}
QuestionBlockTextureFlyWeight* QuestionBlockTextureFlyWeight::GetQuestionBlockTextureFlyWeight()
{
    static QuestionBlockTextureFlyWeight texture;
    return &texture;
}
void QuestionBlockTextureFlyWeight::render(Vector2 Position, Rectangle TextureRect)
{
    // std::cout << "Rendering Question Block at " << Position.x << ", " << Position.y << std::endl;
    DrawTexturePro(m_Texture, TextureRect, Rectangle{Position.x, Position.y, 100, 100}, Vector2{0, 0}, 0.0f, WHITE);
}

QuestionBlock::HitAnimationCommander::HitAnimationCommander(float MoveUpDistance, float BottomPosition) : m_MoveUpDistance(MoveUpDistance), m_BottomPosition(BottomPosition)
{
    m_TopPosition = m_BottomPosition - m_MoveUpDistance;
}
QuestionBlock::HitAnimationCommander::~HitAnimationCommander()
{
}
Vector2 QuestionBlock::HitAnimationCommander::giveMovementCommand(Vector2 CurrentPosition)
{
    if (m_Finished)
    {
        return Vector2{0, 0};
    }
    // std::cout << "Animation Hit\n";
    // std::cout << "Top Position: " << m_TopPosition << std::endl;
    // std::cout << "Current Position: " << CurrentPosition.y << std::endl;
    // std::cout << "Bottom Position: " << m_BottomPosition << std::endl;
    if (!m_HitTop)
    {
        if (CurrentPosition.y < m_TopPosition)
        {
            m_HitTop = true;
            std::cout << "Hit Top\n";
            return Vector2{0, m_TopPosition - CurrentPosition.y};
        }
        else
        {
            return Vector2{0, - m_Speed * GetFrameTime()};
        }
    }
    else
    {
        if (CurrentPosition.y > m_BottomPosition)
        {

            m_Finished = true;
            return Vector2{0, m_BottomPosition - CurrentPosition.y};
        }
        else
        {
            return Vector2{0, m_Speed * GetFrameTime()};
        }
    }
    return Vector2{0, 0};
}
QuestionBlock::QuestionBlock(Vector2 Position) : EnvironmentObjectInteractive(Position, Vector2{100, 100}), m_IdleAnimation(&(QuestionBlockTextureFlyWeight::GetQuestionBlockTextureFlyWeight()->m_Texture), Vector2{4, 1}, 0.17f), m_HitAnimation(20, m_Position.y)
{
}
QuestionBlock::~QuestionBlock()
{
}
void QuestionBlock::render()
{
    // std::cout << "Rendering Question Block at " << m_Position.x << ", " << m_Position.y << std::endl;
    QuestionBlockTextureFlyWeight::GetQuestionBlockTextureFlyWeight()->render(m_Position, getCurrentTextureRect());
}
void QuestionBlock::update()
{
    // std::cout << "Updating Question Block" << std::endl;
    float DeltaTime = GetFrameTime();
    m_IdleAnimation.Update(DeltaTime);
    if (m_IsHit)
    {
        move(m_HitAnimation.giveMovementCommand(m_Position));
    }
}
Rectangle QuestionBlock::getCurrentTextureRect()
{
    return m_IdleAnimation.uvRect;
}
void QuestionBlock::onNotify()
{
    m_IsHit = true;
}
DrawableObjectFactory& DrawableObjectFactory::GetDrawableObjectFactory()
{
    static DrawableObjectFactory Factory;
    return Factory;
}
DrawableObject* DrawableObjectFactory::CreateDrawableObject(int Type, Vector2 Position)
{
    switch (Type)
    {
        case DrawableObjectFactory::DrawableObjectType::CLOUD:
        {
            DrawableObject* cloud = new Cloud(Position);
            return cloud;
        }
        break;
    }
}
CloudTextureFlyWeight::CloudTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/cloud.png");
}
CloudTextureFlyWeight::~CloudTextureFlyWeight()
{
}
CloudTextureFlyWeight* CloudTextureFlyWeight::GetCloudTextureFlyWeight()
{
    static CloudTextureFlyWeight texture;
    return &texture;
}
void CloudTextureFlyWeight::render(Vector2 Position)
{
    DrawTexture(m_Texture, Position.x, Position.y, WHITE);
}
Cloud::Cloud(Vector2 Position) : DrawableObject(Position)
{
}
Cloud::~Cloud()
{
}
void Cloud::render()
{
    CloudTextureFlyWeight::GetCloudTextureFlyWeight()->render(m_Position);
}





