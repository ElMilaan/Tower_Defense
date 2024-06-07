#include <iostream>
#include "Barrage.hpp"

using namespace std;

BarrageLocation Barrage::getLocation()
{
    return location;
}
string Barrage::getSpritePath()
{
    return sprite_path;
}