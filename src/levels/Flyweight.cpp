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

