#include "Environment.hpp"
#include "Level.hpp"
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
        case EnvironmentObjectFactory::EnvironmentObjectType::HARD_BLOCK:
        {
            HardBlock* block = new HardBlock(Position);
            return block;
        }
        case EnvironmentObjectFactory::EnvironmentObjectType::BLUE_BRICK:
        {
            BlueBrick* blueBrick = new BlueBrick(Position);
            return blueBrick;
        }
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
Lift::Lift(Vector2 Position) : MapObject(Position, Vector2{150, 26})
{
}
Lift::~Lift()
{
}
void Lift::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::LIFT)->render(m_Position);
}
void Lift::update(float DeltaTime)
{
    m_Position.y -= m_Speed * DeltaTime;
    if (m_Position.y < -100)
    {
        m_Position.y = 900;
    }
}
Ground::Ground() : MapObject((Vector2{0, 750}), (Vector2{100, 100}))
{
    // m_Texture = LoadTexture("assets/textures/ground1x1.png");
}
Ground::~Ground()
{
}
Ground* Ground::GetGround()
{
    static Ground ground;
    return &ground;
}
void Ground::render()
{
    int PositionX = static_cast<int>(m_CameraPosition.x / m_Size.x);
    for (int i = 0; i < 20; ++i)
    {
        DrawTexture(m_Texture[m_WorldType], i * m_Size.x + m_Size.x * PositionX , m_Position.y, WHITE);
        DrawTexture(m_Texture[m_WorldType], i * m_Size.x + m_Size.x * PositionX , m_Position.y + m_Size.y, WHITE);
    }

    for (auto& hole : m_Holes)
    {
        int Width = hole.second * 100;
        if (m_WorldType == Level::WorldType::OVERWORLD) DrawRectangle(hole.first, m_Position.y, Width, 200, Color{105, 147, 245, 255});
        else if (m_WorldType == Level::WorldType::UNDERGROUND) DrawRectangle(hole.first, m_Position.y, Width, 200, Color{0, 0, 0, 255});
    }
}
void Ground::update(Vector2 CameraPosition)
{
    m_CameraPosition = CameraPosition;
}
void Ground::addHole(float x, unsigned int y)
{
    m_Holes.push_back(std::make_pair(x, y));
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
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::WARP_PIPE)->render(m_Position);
}
void WarpPipe::update()
{
}
Brick::Brick(Vector2 Position) : EnvironmentObject(Position, Vector2{100, 100})
{
}
Brick::~Brick()
{
}
void Brick::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::BRICK)->render(m_Position);
}
void Brick::update()
{
}

HardBlock::HardBlock(Vector2 Position) : EnvironmentObject(Position, Vector2{100, 100})
{
}
HardBlock::~HardBlock()
{
}
void HardBlock::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::HARD_BLOCK)->render(m_Position);
}
void HardBlock::update()
{
}
BlueBrick::BlueBrick(Vector2 Position) : EnvironmentObject(Position, Vector2{100, 100})
{
}
BlueBrick::~BlueBrick()
{
}
void BlueBrick::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::BLUE_BRICK)->render(m_Position);
}
void BlueBrick::update()
{
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
            // std::cout << "Hit Top\n";
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
QuestionBlock::QuestionBlock(Vector2 Position) : EnvironmentObjectInteractive(Position, Vector2{100, 100}), m_IdleAnimation(&(AnimatedFlyweightFactory::GetAnimatedFlyweightFactory()->getFlyweight(TextureType::QUESTION_BLOCK)->getTexture()), Vector2{4, 1}, 0.17f), m_HitAnimation(20, m_Position.y)
{
}
QuestionBlock::~QuestionBlock()
{
}
void QuestionBlock::render()
{
    // std::cout << "Rendering Question Block at " << m_Position.x << ", " << m_Position.y << std::endl;
    if (!m_HitAnimation.isFinished()) QuestionBlockTextureFlyWeight::GetQuestionBlockTextureFlyWeight()->render(m_Position, getCurrentTextureRect());
    // else QuestionBlockTextureFlyWeight::GetQuestionBlockTextureFlyWeight()->render(m_Position, HittedTextureRect);
    else EmptyQuestionBlockTextureFlyweight::GetEmptyQuestionBlockTextureFlyweight()->render(m_Position);
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
        case DrawableObjectFactory::DrawableObjectType::CASTLE:
        {
            DrawableObject* castle = new Castle(Position);
            return castle;
        }
        case DrawableObjectFactory::DrawableObjectType::GRASS:
        {
            DrawableObject* grass = new Grass(Position);
            return grass;
        }
        case DrawableObjectFactory::DrawableObjectType::MOUNTAIN:
        {
            DrawableObject* mountain = new Mountain(Position);
            return mountain;
        }
        default:
        {
            std::cerr << "Invalid Drawable Object Type\n";
            return nullptr;
        }
        break;
    }
}

Cloud::Cloud(Vector2 Position) : DrawableObject(Position)
{
}
Cloud::~Cloud()
{
}
void Cloud::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::CLOUD)->render(m_Position);
}
Grass::Grass(Vector2 Position) : DrawableObject(Position)
{
}
Grass::~Grass()
{
}
void Grass::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::GRASS)->render(m_Position);
}
Mountain::Mountain(Vector2 Position) : DrawableObject(Position)
{
}
Mountain::~Mountain()
{
}
void Mountain::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::MOUNTAIN)->render(m_Position);
}

Castle::Castle(Vector2 Position) : DrawableObject(Position)
{
}
Castle::~Castle()
{
}
void Castle::render()
{
    DrawTexture(m_Texture, m_Position.x, m_Position.y, WHITE);
}

EndPipeTop::EndPipeTop(Vector2 Position) : EnvironmentObject(Position, Vector2{200, 100})
{
}
EndPipeTop::~EndPipeTop()
{
}
void EndPipeTop::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::END_PIPE)->render(m_Position);
}
void EndPipeTop::update()
{
}






