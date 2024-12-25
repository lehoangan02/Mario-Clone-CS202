#include "MapSerializer.hpp"
int main()
{
    MapSerializer& Serializer = MapSerializer::getInstance();
    Serializer.serialize("2.txt", "2.bin");
    Serializer.deserialize("2.bin", "2.txt");
    return 0;
}