#pragma once
#include <vector>
#include "Environment.hpp"
#include "../characters/Character.h"

#include <fstream>
class Level;
class MapLoader
{
    public:
        static MapLoader& GetMapLoader();
        virtual void LoadMap(Level* Level, int MapID);
    protected:
        MapLoader();
        ~MapLoader();
};
class MapLoaderBinary : public MapLoader
{
    public:
        static MapLoaderBinary& GetMapLoaderBinary();
        void LoadMap(Level* Level, int MapID) override;
    private:
        MapLoaderBinary();
        ~MapLoaderBinary();
};