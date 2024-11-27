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
    std::string FileName = std::to_string(MapID) + ".txt";
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
        Level -> m_EnvironmentInteractive.push_back(EnvironmentInteractiveObjectFactory::GetEnvironmentInteractiveFactory().CreateEnvironmentInteractiveObject(Type, Vector2{X, Y}));
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
    fin.close();
}