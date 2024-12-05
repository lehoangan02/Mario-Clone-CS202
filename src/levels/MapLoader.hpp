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
        void LoadMap(Level* Level, int MapID);
    private:
        MapLoader();
        ~MapLoader();
};