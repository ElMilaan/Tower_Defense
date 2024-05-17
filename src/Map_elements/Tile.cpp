#include <iostream>
#include "../Entities/Location.hpp"
#include "Tile.hpp"

using namespace std;

Tile::Tile(double x, double y, bool isStart, bool isEnd)
{
    this->location.setX(x);
    this->location.setY(y);
    this->isStart = isStart;
    this->isEnd = isEnd;
    this->isClosed = false;
}

Location Tile::getLocation()
{
    return this->location;
}

bool Tile::getIsStart()
{
    return isStart;
}

bool Tile::getIsEnd()
{
    return isEnd;
}

bool Tile::getIsClosed()
{
    return isClosed;
}

void Tile::setLocation(Location loc)
{
    this->location = loc;
}

void Tile::toggleIsClosed()
{
    this->isClosed = !isClosed;
}