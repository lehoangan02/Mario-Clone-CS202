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
        case EnemyType::LAKITU:
            {
                Level -> m_Enemies.push_back(Factory.CreateEnemy(EnemyType::LAKITU, Vector2{X, Y}, LeftBound, RightBound));
            }
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
                std::cout << "Creating Fire Flower" << std::endl;
                Texture2D fireflowerTexture = LoadTexture("assets/textures/FireFlower.png");
                NewItem = new FireFlower(
                    Vector2{ X + 20, Y },
                    Vector2{ 0, 0 },
                    Vector2{ 50, 50 },
                    fireflowerTexture
                );
                break;
            }
            case Itemtype::STARMAN:
            {
                std::cout << "Creating Starman" << std::endl;
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
MapLoaderBinary::MapLoaderBinary()
{
}
MapLoaderBinary::~MapLoaderBinary()
{
}
MapLoaderBinary& MapLoaderBinary::GetMapLoaderBinary()
{
    static MapLoaderBinary Loader;
    return Loader;
}
void MapLoaderBinary::LoadMap(Level* Level, int MapID)
{
    std::fstream fin;
    fin.open("Maps/" + std::to_string(MapID) + ".bin", std::ios::in | std::ios::binary);
    if (!fin.is_open())
    {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }
    int CharacterSpawnX, CharacterSpawnY;
    fin.read((char*)&CharacterSpawnX, sizeof(CharacterSpawnX));
    fin.read((char*)&CharacterSpawnY, sizeof(CharacterSpawnY));
    std::cout << "Character Spawn: " << CharacterSpawnX << ", " << CharacterSpawnY << std::endl;
    Level -> m_StartPosition = Vector2{(float)CharacterSpawnX, (float)CharacterSpawnY};
    int NumberOfEnemies;
    fin.read((char*)&NumberOfEnemies, sizeof(NumberOfEnemies));
    std::cout << "Number of Enemies: " << NumberOfEnemies << std::endl;
    for (int i = 0; i < NumberOfEnemies; ++i)
    {
        int Enemytype;
        fin.read((char*)&Enemytype, sizeof(int));
        EnemyType Type = static_cast<EnemyType>(Enemytype);
        int EnemyX, EnemyY;
        fin.read((char*)&EnemyX, sizeof(EnemyX));
        fin.read((char*)&EnemyY, sizeof(EnemyY));
        int EnemyRangeX1, EnemyRangeX2;
        fin.read((char*)&EnemyRangeX1, sizeof(EnemyRangeX1));
        fin.read((char*)&EnemyRangeX2, sizeof(EnemyRangeX2));
        EnemyFactory& Factory = EnemyFactory::GetEnemyFactory();
        Enemy* NewEnemy =  Factory.CreateEnemy(Type, Vector2{(float)EnemyX, (float)EnemyY}, EnemyRangeX1, EnemyRangeX2);
        switch (Enemytype)
        {
            case EnemyType::GOOMBA:
                {
                std::cout << "Creating Goomba" << std::endl;    
                }
                break;
            case EnemyType::KOOPA_TROOPA:
                {
                std::cout << "Creating Koopa Troopa" << std::endl;
                }
                break;
            case EnemyType::PIRANHA_PLANT:
                {
                std::cout << "Creating Piranha Plant" << std::endl;
                }
                break;
            case EnemyType::SHY_GUY:
                {
                std::cout << "Creating Shy Guy" << std::endl;
                }
                break;
            case EnemyType::LAKITU:
                {
                std::cout << "Creating Lakitu" << std::endl;
                }
                break;
            default:
                break;
        }
        Level -> m_Enemies.push_back(NewEnemy);
    }
    int NumberOfItems;
    fin.read((char*)&NumberOfItems, sizeof(NumberOfItems));
    std::cout << "Number of Items: " << NumberOfItems << std::endl;
    for (int i = 0; i < NumberOfItems; ++i)
    {
        int ItemX, ItemY;
        fin.read((char*)&ItemX, sizeof(ItemX));
        fin.read((char*)&ItemY, sizeof(ItemY));
        IdleCoin* Coin = new IdleCoin(Vector2{(float)ItemX, (float)ItemY}, Vector2{40, 100}, LoadTexture("assets/textures/Coin.png"));
        Level -> m_IdleCoin.push_back(Coin);
    }
    int NumberOfStaticEnvironment;
    fin.read((char*)&NumberOfStaticEnvironment, sizeof(NumberOfStaticEnvironment));
    for (int i = 0; i < NumberOfStaticEnvironment; ++i)
    {
        int Type;
        fin.read((char*)&Type, sizeof(Type));
        int X, Y;
        fin.read((char*)&X, sizeof(X));
        fin.read((char*)&Y, sizeof(Y));
        if (Type == EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE)
        {
            Level -> m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(EnvironmentObjectFactory::EnvironmentObjectType::WARP_PIPE, Vector2{(float)X, (float)750 - Y}));
        }
        else
        {
            Level -> m_Environment.push_back(EnvironmentObjectFactory::GetEnvironmentFactory().CreateEnvironmentObject(Type, Vector2{(float)X, (float)Y}));
        }
    }
    int NumberOfInteractiveEnvironment;
    fin.read((char*)&NumberOfInteractiveEnvironment, sizeof(NumberOfInteractiveEnvironment));
    std::cout << "Number of Interactive Environment: " << NumberOfInteractiveEnvironment << std::endl;

    for (int i = 0; i < NumberOfInteractiveEnvironment; ++i)
    {
        std::cout << "i: " << i << std::endl;
        int Type;
        fin.read((char*)&Type, sizeof(Type));
        switch (Type)
        {
        case EnvironmentInteractiveObjectFactory::EnvironmentInteractiveObjectType::QUESTION_BLOCK:
        {
            std::cout << "Creating Question Block" << std::endl;
            break;
        }
        case EnvironmentInteractiveObjectFactory::EnvironmentInteractiveObjectType::BREAKABLE_BRICK:
        {
            std::cout << "Creating Breakable Brick" << std::endl;
            break;
        }
        default:
            break;
        }
        int PositionX, PositionY;
        fin.read((char*)&PositionX, sizeof(int));
        fin.read((char*)&PositionY, sizeof(int));
        float X = static_cast<float>(PositionX);
        float Y = static_cast<float>(PositionY);
        
        std::cout << "Creating Interactive Environment Object at " << X << ", " << Y << std::endl;
        int ItemType;
        fin.read((char*)&ItemType, sizeof(ItemType));
        std::cout << "Item Type: " << ItemType << std::endl;
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
                std::cout << "Creating Coin" << std::endl;
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
                std::cout << "Creating Mushroom" << std::endl;
                break;
            case Itemtype::FIREFLOWER:
            {
                std::cout << "Creating Fire Flower" << std::endl;
                Texture2D fireflowerTexture = LoadTexture("assets/textures/FireFlower.png");
                NewItem = new FireFlower(
                    Vector2{ X + 20, Y },
                    Vector2{ 0, 0 },
                    Vector2{ 50, 50 },
                    fireflowerTexture
                );

                break;
            }
            case Itemtype::STARMAN:
            {
                std::cout << "Creating Starman" << std::endl;
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
   /* std::cout << "Number of Drawables: " << NumberOfDrawables << std::endl;*/
    fin.read((char*)&NumberOfDrawables, sizeof(NumberOfDrawables));
    for (int i = 0; i < NumberOfDrawables; ++i)
    {
        int Type;
        fin.read((char*)&Type, sizeof(Type));
        int X, Y;
        fin.read((char*)&X, sizeof(X));
        fin.read((char*)&Y, sizeof(Y));
        Level -> m_Drawables.push_back(DrawableObjectFactory::GetDrawableObjectFactory().CreateDrawableObject(Type, Vector2{(float)X, (float)Y}));
    }
    Level -> m_Ground -> reset();
    int NumberOfHoles;
    fin.read((char*)&NumberOfHoles, sizeof(NumberOfHoles));
    std::cout << "Number of Holes: " << NumberOfHoles << std::endl;
    for (int i = 0; i < NumberOfHoles; ++i)
    {
        int X;
        unsigned int Y;
        fin.read((char*)&X, sizeof(X));
        fin.read((char*)&Y, sizeof(Y));
        Level -> m_Ground -> addHole(X, Y);
    }
    int NumberOfLifts;
    fin.read((char*)&NumberOfLifts, sizeof(NumberOfLifts));
    for (int i = 0; i < NumberOfLifts; ++i)
    {
        int X, Y;
        fin.read((char*)&X, sizeof(X));
        fin.read((char*)&Y, sizeof(Y));
        Level -> m_Lifts.push_back(new Lift(Vector2{float(X), float(Y)}));
    }
    int NumberOfEndPipes;
    fin.read((char*)&NumberOfEndPipes, sizeof(NumberOfEndPipes));
    for (int i = 0; i < NumberOfEndPipes; ++i)
    {
        int Type;
        fin.read((char*)&Type, sizeof(Type));
        int X, Y;
        fin.read((char*)&X, sizeof(X));
        fin.read((char*)&Y, sizeof(Y));
        if (Type == EndPipeType::TOP)
        {
            EndPipeTop* Pipe = new EndPipeTop(Vector2{(float)X, (float)(750 - Y)});
            Level -> m_EndPipeHandler.addEndPipe(Pipe);
            Level -> m_EndPipes.push_back(Pipe);
        }
        else
        {
            EndPipeSide* Pipe = new EndPipeSide(Vector2{(float)X, float(750 - Y)});
            Level -> m_EndPipeHandler.addEndPipe(Pipe);
            Level -> m_EndPipes.push_back(Pipe);
        }
    }
    int WorldType;
    fin.read((char*)&WorldType, sizeof(WorldType));
    std::cout << "World Type: " << WorldType << std::endl;
    Level -> m_Ground -> setWorldType(WorldType);
    int HaveFlagPole;
    fin.read((char*)&HaveFlagPole, sizeof(HaveFlagPole));
    if (HaveFlagPole)
    {
        int X;
        fin.read((char*)&X, sizeof(X));
        std::cout << "Creating Flag Pole at " << X << std::endl;
        FlagPole* Pole = new FlagPole(X);
        Level -> m_FlagPole = Pole;
    }
    fin.close();
}