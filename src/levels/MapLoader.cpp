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
    int NumberOfEnemies;
    fin >> NumberOfEnemies;
    int NumberOfItems;
    fin >> NumberOfItems;
    int NumberOfStaticEnvironment;
    fin >> NumberOfStaticEnvironment;
    for (int i = 0; i < NumberOfStaticEnvironment; i++)
    {
        int Type;
        fin >> Type;
        float X, Y;
        fin >> X >> Y;
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
    for (int i = 0; i < NumberOfInteractiveEnvironment; i++)
    {
        int Type;
        fin >> Type;
        float X, Y;
        fin >> X >> Y;
        int ItemType;
        fin >> ItemType;
        std::pair<EnvironmentObjectInteractive*, Item*> Pair;
        Pair.first = EnvironmentInteractiveObjectFactory::GetEnvironmentInteractiveFactory().CreateEnvironmentInteractiveObject(Type, Vector2{X, Y});
        std::cout << "asdlfkjasldfkj" << Pair.first << std::endl;
        Coin* coin = new Coin(
            Vector2{ X + 40, Y },   //Start position
            Vector2{ X + 40, Y - 300 },    //End position
            Vector2{ 40,100},      // size of coin
            LoadTexture("assets/textures/Coin.png"),
            Vector2{ 0, 400 }     //velocity
        );
        Pair.second = coin;
        Level -> m_EnvironmentInteractive.push_back(Pair);
    }
    int NumberOfDrawables;
    fin >> NumberOfDrawables;
    for (int i = 0; i < NumberOfDrawables; i++)
    {
        int Type;
        fin >> Type;
        float X, Y;
        fin >> X >> Y;
        Level -> m_Drawables.push_back(DrawableObjectFactory::GetDrawableObjectFactory().CreateDrawableObject(Type, Vector2{X, Y}));
    }
    Level -> m_Ground -> clearHoles();
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
        Level -> m_EndPipes.push_back(new EndPipeTop(Vector2{X, 750 - Y}));
    }
    int WorldType;
    fin >> WorldType;
    Level -> m_WorldType = WorldType;
    Level -> m_Ground -> setWorldType(WorldType);
    fin.close();
}