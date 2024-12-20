#include "MapLoader.hpp"
#include "Level.hpp"
MapLoader& MapLoader::GetMapLoader()
{
    static MapLoader Loader;
    return Loader;
}
MapLoader::MapLoader()
{
}
MapLoader::~MapLoader()
{
}
void MapLoader::LoadMap(Level* Level, int MapID)
{
    std::string FileName = "Maps/" + std::to_string(MapID) + ".txt";
    std::ifstream fin;
    fin.open(FileName);
    if (!fin.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    Vector2 PlayerSpawn;
    fin >> PlayerSpawn.x >> PlayerSpawn.y;
    Level -> m_StartPosition = PlayerSpawn;
    int NumberOfEnemies;
    fin >> NumberOfEnemies;
    for (int i = 0; i < NumberOfEnemies; i++)
    {
        int Type;
        fin >> Type;
        float X, Y;
        fin >> X >> Y;
        float LeftBound, RightBound;
        fin >> LeftBound >> RightBound;
        EnemyFactory& Factory = EnemyFactory::GetEnemyFactory();
        switch (Type)
        {
        case EnemyType::GOOMBA:
            {
                Level -> m_Enemies.push_back(Factory.CreateEnemy(EnemyType::GOOMBA, Vector2{X, Y}, LeftBound, RightBound));
            }
            break;
        case EnemyType::KOOPA_TROOPA:
            {
                Level -> m_Enemies.push_back(Factory.CreateEnemy(EnemyType::KOOPA_TROOPA, Vector2{X, Y}, LeftBound, RightBound));
            }
            break;
        case EnemyType::PIRANHA_PLANT:
            {
                Level -> m_Enemies.push_back(Factory.CreateEnemy(EnemyType::PIRANHA_PLANT, Vector2{X, Y}, LeftBound, RightBound));
            }
            break;
        case EnemyType::SHY_GUY:
            {
                Level -> m_Enemies.push_back(Factory.CreateEnemy(EnemyType::SHY_GUY, Vector2{X, Y}, LeftBound, RightBound));
            }
            break;
        default:
            break;
        }
    }
    int NumberOfItems;
    fin >> NumberOfItems;
    for (int i = 0; i < NumberOfItems; i++)
    {
    
        float X, Y;
        fin >> X >> Y;
        IdleCoin* Coin = new IdleCoin(Vector2{X, Y}, Vector2{40, 100}, LoadTexture("assets/textures/Coin.png"));
        Level -> m_IdleCoin.push_back(Coin);
    }
    int NumberOfStaticEnvironment;
    fin >> NumberOfStaticEnvironment;
    std::cout << "Number of Static Environment: " << NumberOfStaticEnvironment << std::endl;
    for (int i = 0; i < NumberOfStaticEnvironment; i++)
    {
        int Type;
        fin >> Type;
        float X, Y;
        fin >> X >> Y;
        std::cout << "Creating Static Environment Object at " << X << ", " << Y << std::endl;
        if (Type == EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE)
        {
            Level->m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE, Vector2{X, 750 - Y}));
        }
        else
        {
            Level -> m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(Type, Vector2{X, Y}));
        }
    }
    int NumberOfInteractiveEnvironment;
    fin >> NumberOfInteractiveEnvironment;
    std::cout << "Number of Interactive Environment: " << NumberOfInteractiveEnvironment << std::endl;
    for (int i = 0; i < NumberOfInteractiveEnvironment; i++)
    {
        int Type;
        fin >> Type;
        float X, Y;
        fin >> X >> Y;
        int ItemType;
        fin >> ItemType;
        Itemtype MyItemType = static_cast<Itemtype>(ItemType);
        std::pair<EnvironmentObjectInteractive*, Item*> Pair;
        Pair.first = EnvironmentInteractiveObjectFactory::GetEnvironmentInteractiveFactory().CreateEnvironmentInteractiveObject(Type, Vector2{X, Y});
        Item* NewItem = nullptr;
        if (Pair.first->getObjectID() == EnvironmentInteractiveObjectFactory::EnvironmentInteractiveObjectType::QUESTION_BLOCK)
        {
                switch (MyItemType)
            {
            case Itemtype::COIN:
                {
                    NewItem = new Coin(
                    Vector2{ X + 40, Y },   //Start position
                    Vector2{ X + 40, Y - 300 },    //End position
                    Vector2{ 40,100},      // size of coin
                    LoadTexture("assets/textures/Coin.png"),
                    Vector2{ 0, 400 }     //velocity
                    );
                }
                break;
            case Itemtype::MUSHROOM:
                {
                    NewItem = new Mushroom(
                    Vector2{ X + 20, Y},   //Start position
                    Vector2{ 0, 0 },    //End position
                    Vector2{ 50, 50},      // size of coin
                    LoadTexture("assets/textures/MagicMushroom.png"),
                    Vector2{ 100, 0 }     //velocity
                    );
                }
                break;
            case Itemtype::FIREFLOWER:
            {
                Texture2D fireflowerTexture = LoadTexture("assets/textures/FireFlower.png");
                NewItem = new FireFlower(
                    Vector2{ X + 20, Y },
                    Vector2{ 0, 0 },
                    Vector2{ 50, 50 },
                    fireflowerTexture
                );
            }
            case Itemtype::STARMAN:
            {
                Texture2D starmanTexture = LoadTexture("assets/textures/starman.png");
                NewItem = new StarMan(
                    Vector2{ X + 20, Y },
                    Vector2{ 0, 0 },
                    Vector2{ 60, 60 },
                    starmanTexture,
                    Vector2{ 3.0f, 3.0f }
                );
                break;
            }
            default:
                NewItem = nullptr;
                break;
            }
        }
        Pair.second = NewItem;
        Level -> m_EnvironmentInteractive.push_back(Pair);
    }
    int NumberOfDrawables;
    fin >> NumberOfDrawables;
    std::cout << "Number of Drawables: " << NumberOfDrawables << std::endl;
    for (int i = 0; i < NumberOfDrawables; i++)
    {
        int Type;
        fin >> Type;
        float X, Y;
        fin >> X >> Y;
        Level -> m_Drawables.push_back(DrawableObjectFactory::GetDrawableObjectFactory().CreateDrawableObject(Type, Vector2{X, Y}));
    }
    Level -> m_Ground -> reset();
    int NumberOfHoles;
    fin >> NumberOfHoles;
    for (int i = 0; i < NumberOfHoles; i++)
    {
        float X;
        unsigned int Y;
        fin >> X >> Y;
        Level -> m_Ground -> addHole(X, Y);
    }
    int NumberOfLifts;
    fin >> NumberOfLifts;
    for (int i = 0; i < NumberOfLifts; i++)
    {
        float X, Y;
        fin >> X >> Y;
        Level -> m_Lifts.push_back(new Lift(Vector2{X, Y}));
    }
    int NumberOfEndPipes;
    fin >> NumberOfEndPipes;
    for (int i = 0; i < NumberOfEndPipes; i++)
    {
        int Type;
        fin >> Type;
        float X, Y;
        fin >> X >> Y;
        if (Type == EndPipeType::TOP)
        {
            EndPipeTop* Pipe = new EndPipeTop(Vector2{X, 750 - Y});
            Level -> m_EndPipeHandler.addEndPipe(Pipe);
            Level -> m_EndPipes.push_back(Pipe);
        }
        else
        {
            EndPipeSide* Pipe = new EndPipeSide(Vector2{X, 750 - Y});
            Level -> m_EndPipeHandler.addEndPipe(Pipe);
            Level -> m_EndPipes.push_back(Pipe);
        }
    }
    int WorldType;
    fin >> WorldType;
    Level -> m_Ground -> setWorldType(WorldType);
    bool HaveFlagPole;
    fin >> HaveFlagPole;
    if (HaveFlagPole)
    {
        float X;
        fin >> X;
        FlagPole* Pole = new FlagPole(X);
        Level -> m_FlagPole = Pole;
    }
    fin.close();
}