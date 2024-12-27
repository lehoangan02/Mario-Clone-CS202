#include "MapSerializer.hpp"
int main()
{
    MapSerializer& Serializer = MapSerializer::getInstance();
    Serializer.serialize("7.txt", "7.bin");
    Serializer.deserialize("7.bin", "7.txt");
    return 0;
}