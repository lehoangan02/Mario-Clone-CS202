#include "Flyweight.hpp"
StaticFlyweight* StaticFlyweightFactory::getFlyweight(int Type)
{
    switch (Type)
    {
        case TextureType::WARP_PIPE:
        {
            return WarpPipeTextureFlyWeight::GetWarpPipeTextureFlyweight();
        }
        break;
        case TextureType::BRICK:
        {
            return BrickTextureFlyWeight::GetBrickTextureFlyWeight();
        }
        break;
        case TextureType::HARD_BLOCK:
        {
            return HardBlockTextureFlyWeight::GetHardBlockTextureFlyWeight();
        }
        break;
        case TextureType::CLOUD:
        {
            return CloudTextureFlyWeight::GetCloudTextureFlyWeight();
        }
        case TextureType::BLUE_BRICK:
        {
            return BlueBrickTextureFlyWeight::GetBlueBrickTextureFlyWeight();
        }
        case TextureType::LIFT:
        {
            return LiftTextureFlyWeight::GetLiftTextureFlyWeight();
        }
        case TextureType::GRASS:
        {
            return GrassTextureFlyWeight::GetGrassTextureFlyWeight();
        }
        case TextureType::MOUNTAIN:
        {
            return MountainTextureFlyWeight::GetMountainTextureFlyWeight();
        }
        case TextureType::END_PIPE:
        {
            return EndPipeTopTextureFlyWeight::GetEndPipeTextureFlyWeight();
        }
        case TextureType::EMPTY_QUESTION_BLOCK:
        {
            return EmptyQuestionBlockTextureFlyweight::GetEmptyQuestionBlockTextureFlyweight();
        }
        case TextureType::DIRT:
        {
            return DirtTextureFlyWeight::GetDirtTextureFlyWeight();
        }
        case TextureType::LEFT_GRASS_PLATFORM:
        {
            return LeftGrassPlatformTextureFlyWeight::GetLeftGrassPlatformTextureFlyWeight();
        }
        case TextureType::MID_GRASS_PLATFORM:
        {
            return MiddleGrassPlatformTextureFlyWeight::GetMiddleGrassPlatformTextureFlyWeight();
        }
        case TextureType::RIGHT_GRASS_PLATFORM:
        {
            return RightGrassPlatformTextureFlyWeight::GetRightGrassPlatformTextureFlyWeight();
        }
        break;
    }
    return nullptr;
}
StaticFlyweightFactory* StaticFlyweightFactory::GetStaticFlyweightFactory()
{
    static StaticFlyweightFactory Factory;
    return &Factory;
}
AnimatedFlyweightFactory* AnimatedFlyweightFactory::GetAnimatedFlyweightFactory()
{
    static AnimatedFlyweightFactory Factory;
    return &Factory;
}
AniamtedFlyweight* AnimatedFlyweightFactory::getFlyweight(int Type)
{
    switch (Type)
    {
        case TextureType::QUESTION_BLOCK:
        {
            return QuestionBlockTextureFlyWeight::GetQuestionBlockTextureFlyWeight();
        }
        break;
    }
    return nullptr;
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
BrickTextureFlyWeight::BrickTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/brick_2.png");
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
    DrawTextureEx(m_Texture, Position, 0.0f, 6.25f, WHITE);
}
HardBlockTextureFlyWeight::HardBlockTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/hard_block.png");
}
HardBlockTextureFlyWeight::~HardBlockTextureFlyWeight()
{
}
HardBlockTextureFlyWeight* HardBlockTextureFlyWeight::GetHardBlockTextureFlyWeight()
{
    static HardBlockTextureFlyWeight texture;
    return &texture;
}
void HardBlockTextureFlyWeight::render(Vector2 Position)
{
    DrawTexture(m_Texture, Position.x, Position.y, WHITE);
}
BlueBrickTextureFlyWeight::BlueBrickTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/blue_brick.png");
}
BlueBrickTextureFlyWeight::~BlueBrickTextureFlyWeight()
{
}
BlueBrickTextureFlyWeight* BlueBrickTextureFlyWeight::GetBlueBrickTextureFlyWeight()
{
    static BlueBrickTextureFlyWeight texture;
    return &texture;
}
void BlueBrickTextureFlyWeight::render(Vector2 Position)
{
    DrawTexture(m_Texture, Position.x, Position.y, WHITE);
}
LeftGrassPlatformTextureFlyWeight::LeftGrassPlatformTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/LeftGrassPlatform.png");
}
LeftGrassPlatformTextureFlyWeight::~LeftGrassPlatformTextureFlyWeight()
{
}
LeftGrassPlatformTextureFlyWeight* LeftGrassPlatformTextureFlyWeight::GetLeftGrassPlatformTextureFlyWeight()
{
    static LeftGrassPlatformTextureFlyWeight texture;
    return &texture;
}
void LeftGrassPlatformTextureFlyWeight::render(Vector2 Position)
{
    DrawTextureEx(m_Texture, Position, 0.0f, 6.25f, WHITE);
}
MiddleGrassPlatformTextureFlyWeight::MiddleGrassPlatformTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/MiddleGrassPlatform.png");
}
MiddleGrassPlatformTextureFlyWeight::~MiddleGrassPlatformTextureFlyWeight()
{
}
MiddleGrassPlatformTextureFlyWeight* MiddleGrassPlatformTextureFlyWeight::GetMiddleGrassPlatformTextureFlyWeight()
{
    static MiddleGrassPlatformTextureFlyWeight texture;
    return &texture;
}
void MiddleGrassPlatformTextureFlyWeight::render(Vector2 Position)
{
    DrawTextureEx(m_Texture, Position, 0.0f, 6.25f, WHITE);
}
RightGrassPlatformTextureFlyWeight::RightGrassPlatformTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/RightGrassPlatform.png");
}

RightGrassPlatformTextureFlyWeight::~RightGrassPlatformTextureFlyWeight()
{
}
RightGrassPlatformTextureFlyWeight* RightGrassPlatformTextureFlyWeight::GetRightGrassPlatformTextureFlyWeight()
{
    static RightGrassPlatformTextureFlyWeight texture;
    return &texture;
}
void RightGrassPlatformTextureFlyWeight::render(Vector2 Position)
{
    DrawTextureEx(m_Texture, Position, 0.0f, 6.25f, WHITE);
}

LiftTextureFlyWeight::LiftTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/lift.png");
}
LiftTextureFlyWeight::~LiftTextureFlyWeight()
{
}
LiftTextureFlyWeight* LiftTextureFlyWeight::GetLiftTextureFlyWeight()
{
    static LiftTextureFlyWeight texture;
    return &texture;
}
void LiftTextureFlyWeight::render(Vector2 Position)
{
    DrawTexture(m_Texture, Position.x, Position.y, WHITE);
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
EmptyQuestionBlockTextureFlyweight::EmptyQuestionBlockTextureFlyweight()
{
    m_Texture = LoadTexture("assets/textures/empty_question_block_2.png");
}
EmptyQuestionBlockTextureFlyweight::~EmptyQuestionBlockTextureFlyweight()
{
}
EmptyQuestionBlockTextureFlyweight* EmptyQuestionBlockTextureFlyweight::GetEmptyQuestionBlockTextureFlyweight()
{
    static EmptyQuestionBlockTextureFlyweight texture;
    return &texture;
}
void EmptyQuestionBlockTextureFlyweight::render(Vector2 Position)
{
    DrawTextureEx(m_Texture, Position, 0.0f, 6.25f, WHITE);
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
GrassTextureFlyWeight::GrassTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/grass.png");
}
GrassTextureFlyWeight::~GrassTextureFlyWeight()
{
}
GrassTextureFlyWeight* GrassTextureFlyWeight::GetGrassTextureFlyWeight()
{
    static GrassTextureFlyWeight texture;
    return &texture;
}
void GrassTextureFlyWeight::render(Vector2 Position)
{
    DrawTexture(m_Texture, Position.x, Position.y, WHITE);
}
MountainTextureFlyWeight::MountainTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/mountain.png");
}
MountainTextureFlyWeight::~MountainTextureFlyWeight()
{
}
MountainTextureFlyWeight* MountainTextureFlyWeight::GetMountainTextureFlyWeight()
{
    static MountainTextureFlyWeight texture;
    return &texture;
}
void MountainTextureFlyWeight::render(Vector2 Position)
{
    DrawTexture(m_Texture, Position.x, Position.y, WHITE);
}
DirtTextureFlyWeight::DirtTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/Dirt.png");
}
DirtTextureFlyWeight::~DirtTextureFlyWeight()
{
}
DirtTextureFlyWeight* DirtTextureFlyWeight::GetDirtTextureFlyWeight()
{
    static DirtTextureFlyWeight texture;
    return &texture;
}
void DirtTextureFlyWeight::render(Vector2 Position)
{
    DrawTextureEx(m_Texture, Position, 0, 6.25, WHITE);
}

EndPipeTopTextureFlyWeight::EndPipeTopTextureFlyWeight()
{
    m_Texture = LoadTexture("assets/textures/end_pipe.png");
    SetTextureFilter(m_Texture, TEXTURE_FILTER_POINT);
}
EndPipeTopTextureFlyWeight::~EndPipeTopTextureFlyWeight()
{
}
EndPipeTopTextureFlyWeight* EndPipeTopTextureFlyWeight::GetEndPipeTextureFlyWeight()
{
    static EndPipeTopTextureFlyWeight texture;
    return &texture;
}
void EndPipeTopTextureFlyWeight::render(Vector2 Position)
{
    DrawTextureEx(m_Texture, Position, 0.0f, 3.125, WHITE);
}


