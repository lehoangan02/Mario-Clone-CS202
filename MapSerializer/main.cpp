#include "MapSerializer.hpp"
int main()
{
    MapSerializer& Serializer = MapSerializer::getInstance();
    Serializer.serialize("3.txt", "3.bin");
    Serializer.deserialize("3.bin", "3.txt");
    return 0;
}