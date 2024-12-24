//
// Created by Le Hoang An on 24/12/24.
//

#ifndef MAPSERIALIZE_MAPSERIALIZER_HPP
#define MAPSERIALIZE_MAPSERIALIZER_HPP

#endif //MAPSERIALIZE_MAPSERIALIZER_HPP
#include <string>
#include <iostream>
#include <fstream>
class MapSerializer {
private:
    MapSerializer() = default;
    ~MapSerializer() = default;
public:
    static MapSerializer& getInstance() {
        static MapSerializer instance;
        return instance;
    }
    void serialize(std::string inputFile, std::string outputFile);
    void deserialize(std::string inputFile, std::string outputFile);
};