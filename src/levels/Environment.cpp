#include "Environment.hpp"
#include "Level.hpp"
#include "AABBox.hpp"
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
            // std::cout << "Creating Warp Pipe at " << Position.x << ", " << Position.y << std::endl;
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
        case EnvironmentObjectFactory::EnvironmentObjectType::LEFT_GRASS_PLATFORM:
        {
            LeftGrassPlatform* leftGrassPlatform = new LeftGrassPlatform(Position);
            return leftGrassPlatform;
        }
        case EnvironmentObjectFactory::EnvironmentObjectType::MID_GRASS_PLATFORM:
        {
            MiddleGrassPlatform* midGrassPlatform = new MiddleGrassPlatform(Position);
            return midGrassPlatform;
        }
        case EnvironmentObjectFactory::EnvironmentObjectType::RIGHT_GRASS_PLATFORM:
        {
            RightGrassPlatform* rightGrassPlatform = new RightGrassPlatform(Position);
            return rightGrassPlatform;
        }
        case EnvironmentObjectFactory::EnvironmentObjectType::BLUE_HARD_BLOCK:
        {
            BlueHardBlock* blueHardBlock = new BlueHardBlock(Position);
            return blueHardBlock;
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
        case EnvironmentInteractiveObjectFactory::EnvironmentInteractiveObjectType::BREAKABLE_BRICK:
        {
            BreakableBrick* brick = new BreakableBrick(Position);
            return brick;
        }
        default:
        {
            std::cerr << "Invalid Environment Interactive Object Type\n";
            return nullptr;
        }
    }
    return nullptr;
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
    // std::cout << "Number of Holes: " << m_Holes.size() << std::endl;
    int PositionX = static_cast<int>(m_CameraPosition.x / m_Size.x);
    for (int i = 0; i < 40; ++i)
    {
        if (m_HoleSet.find(i + PositionX) != m_HoleSet.end())
        {

        }
        else
        {
            DrawTexture(m_Texture[m_WorldType], i * m_Size.x + m_Size.x * PositionX , m_Position.y, WHITE);
            DrawTexture(m_Texture[m_WorldType], i * m_Size.x + m_Size.x * PositionX , m_Position.y + m_Size.y, WHITE);
        }
    }

    // for (auto& hole : m_Holes)
    // {
    //     int Width = hole.second * 100;
    //     if (m_WorldType == Level::WorldType::OVERWORLD) DrawRectangle(hole.first, m_Position.y, Width, 200, Color{105, 147, 245, 255});
    //     else if (m_WorldType == Level::WorldType::UNDERGROUND) DrawRectangle(hole.first, m_Position.y, Width, 200, Color{0, 0, 0, 255});
    // }
}
void Ground::reset()
{
    m_Holes.clear();
    m_HoleSet.clear();
}
void Ground::update(Vector2 CameraPosition)
{
    m_CameraPosition = CameraPosition;
}
void Ground::addHole(float x, unsigned int y)
{
    int HolePosition = static_cast<int>(x / m_Size.x);
    for (int i = 0; i < y; ++i)
    {
        m_HoleSet.insert(HolePosition + i);
    }
    m_Holes.push_back(std::make_pair(x, y));
}
bool Ground::isInHole(AABBox Box)
{
    for (auto& hole : m_Holes)
    {
        if (Box.getPosition().x + Box.getSize().x < hole.first + hole.second * 100 && Box.getPosition().x > hole.first)
        {
            return true;
        }
    }
    return false;
}

WarpPipe::WarpPipe(Vector2 Position) : EnvironmentObject(Position, Vector2{209, 195})
{
    m_Type = EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE;
}
WarpPipe::~WarpPipe()
{
}
void WarpPipe::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::WARP_PIPE)->render(m_Position);
}
void WarpPipe::update()
{
}
Brick::Brick(Vector2 Position) : EnvironmentObject(Position, Vector2{100, 100})
{
    m_Type = EnvironmentObjectFactory::EnvironmentObjectType::BRICK;
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
    m_Type = EnvironmentObjectFactory::EnvironmentObjectType::HARD_BLOCK;
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
    m_Type = EnvironmentObjectFactory::EnvironmentObjectType::BLUE_BRICK;
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
LeftGrassPlatform::LeftGrassPlatform(Vector2 Position) : EnvironmentObject(Position, Vector2{100, 100})
{
    m_Type = EnvironmentObjectFactory::EnvironmentObjectType::LEFT_GRASS_PLATFORM;
}
LeftGrassPlatform::~LeftGrassPlatform()
{
}
void LeftGrassPlatform::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::LEFT_GRASS_PLATFORM)->render(m_Position);
}
void LeftGrassPlatform::update()
{
}
MiddleGrassPlatform::MiddleGrassPlatform(Vector2 Position) : EnvironmentObject(Position, Vector2{100, 100})
{
    m_Type = EnvironmentObjectFactory::EnvironmentObjectType::MID_GRASS_PLATFORM;
}
MiddleGrassPlatform::~MiddleGrassPlatform()
{
}
void MiddleGrassPlatform::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::MID_GRASS_PLATFORM)->render(m_Position);
}
void MiddleGrassPlatform::update()
{
}
RightGrassPlatform::RightGrassPlatform(Vector2 Position) : EnvironmentObject(Position, Vector2{100, 100})
{
    m_Type = EnvironmentObjectFactory::EnvironmentObjectType::RIGHT_GRASS_PLATFORM;
}
RightGrassPlatform::~RightGrassPlatform()
{
}
void RightGrassPlatform::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::RIGHT_GRASS_PLATFORM)->render(m_Position);
}
void RightGrassPlatform::update()
{
}
BlueHardBlock::BlueHardBlock(Vector2 Position) : EnvironmentObject(Position, Vector2{100, 100})
{
    m_Type = EnvironmentObjectFactory::EnvironmentObjectType::BLUE_HARD_BLOCK;
}
BlueHardBlock::~BlueHardBlock()
{
}
void BlueHardBlock::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::BLUE_HARD_BLOCK)->render(m_Position);
}
void BlueHardBlock::update()
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
    if (!m_IsHit) QuestionBlockTextureFlyWeight::GetQuestionBlockTextureFlyWeight()->render(m_Position, getCurrentTextureRect());
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
BreakableBrick::BreakableBrick(Vector2 Position) : EnvironmentObjectInteractive(Position, Vector2{100, 100}),
 m_BreakAnimation(&m_AnimatedTexture, Vector2{3, 1}, 0.3f)
{
    m_BreakAnimation.setTexture(&m_AnimatedTexture);
}
BreakableBrick::~BreakableBrick()
{
}
void BreakableBrick::render()
{
    if (!m_IsHit)
    {
        DrawTextureEx(m_Texture, m_Position, 0, 6.25f, WHITE);
    }
    else
    {
        if (!(m_BreakAnimation.isFinished()))
        {
            m_BreakAnimation.draw(m_Position, 6.25f);
        }
        else
        {
            // std::cout << "Finished Animation" << std::endl;
        }
    }
}
void BreakableBrick::update()
{
    if (m_IsHit)
    {
        // std::cout << "Updating Animation" << std::endl;
        m_BreakAnimation.Update(GetFrameTime());
    }
    if (IsKeyPressed(KEY_B))
    {
        onNotify();
    }
}
bool BreakableBrick::isHit()
{
    return m_IsHit;
}
void BreakableBrick::onNotify()
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
        case DrawableObjectFactory::DrawableObjectType::DIRT:
        {
            DrawableObject* dirt = new Dirt(Position);
            return dirt;
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
Dirt::Dirt(Vector2 Position) : DrawableObject(Position)
{
}
Dirt::~Dirt()
{
}
void Dirt::render()
{ 
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::DIRT)->render(m_Position);
}


Castle::Castle(Vector2 Position) : DrawableObject(Position)
{
    SetTextureFilter(m_Texture, TEXTURE_FILTER_POINT);
    SetTextureWrap(m_Texture, TEXTURE_WRAP_CLAMP);
}
Castle::~Castle()
{
}
void Castle::render()
{
    DrawTextureEx(m_Texture, m_Position, 0, 2, WHITE);
}

EndPipe::EndPipe(Vector2 Position, Vector2 Size, int Type) : EnvironmentObject(Position, Size), m_Type(Type)
{
}
EndPipe::~EndPipe()
{
}
EndPipeTop::EndPipeTop(Vector2 Position) : EndPipe(Position, Vector2{200, 100}, EndPipeType::TOP)
{
}
EndPipeTop::~EndPipeTop()
{
}
void EndPipeTop::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::END_PIPE_TOP)->render(m_Position);
}
void EndPipeTop::update()
{
}
EndPipeSide::EndPipeSide(Vector2 Position) : EndPipe(Position, Vector2{100, 100}, EndPipeType::SIDE)
{
}
EndPipeSide::~EndPipeSide()
{
}
void EndPipeSide::render()
{
    StaticFlyweightFactory::GetStaticFlyweightFactory()->getFlyweight(TextureType::END_PIPE_SIDE)->render(m_Position);
}
void EndPipeSide::update()
{
}
FlagPole::FlagPole(float Position) : MapObject(Vector2{Position, 100}, Vector2{100, 900})
{
    m_Position.x = Position;
    m_Position.y = 750 - 900;
    m_FlagPosition = {m_Position.x - 50, m_Position.y + 50};
    SetTextureFilter(m_Flag, TEXTURE_FILTER_POINT);
    SetTextureWrap(m_Flag, TEXTURE_WRAP_CLAMP);
    SetTextureFilter(m_Pole, TEXTURE_FILTER_POINT);
    SetTextureWrap(m_Pole, TEXTURE_WRAP_CLAMP);
    SetTextureFilter(m_Brick, TEXTURE_FILTER_POINT);
    SetTextureWrap(m_Brick, TEXTURE_WRAP_CLAMP);
}
FlagPole::~FlagPole()
{
}
void FlagPole::render()
{
    DrawTextureEx(m_Flag, m_FlagPosition, 0, 5, WHITE);
    DrawTextureEx(m_Pole, m_Position, 0, 5, WHITE);
    DrawTextureEx(m_Brick, {m_Position.x, m_Position.y + 800}, 0, 1, WHITE);
}
void FlagPole::update()
{
    if (IsKeyPressed(KEY_ZERO))
    {
        notifyPull();
    }
    pullFlag();
}
void FlagPole::pullFlag()
{
    if (!m_Pull) return;
    static const float Speed = 600;
    static const float EndPosition = 750 - 200;
    m_FlagPosition.y += Speed * GetFrameTime();
    if (m_FlagPosition.y > EndPosition)
    {
        m_FlagPosition.y = EndPosition;
        m_Done = true;
    }
}
void FlagPole::notifyPull()
{
    m_Pull = true;
}





