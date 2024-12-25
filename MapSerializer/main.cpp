#include "MapSerializer.hpp"
int main()
{
    MapSerializer& Serializer = MapSerializer::getInstance();
    Serializer.serialize("input.txt", "output.txt");
    Serializer.deserialize("output.txt", "output.txt");
    return 0;
}