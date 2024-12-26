#include "MapSerializer.hpp"
int main()
{
    MapSerializer& Serializer = MapSerializer::getInstance();
    Serializer.serialize("0.txt", "0.bin");
    Serializer.deserialize("0.bin", "0.txt");
    return 0;
}