#include <iostream>
#include "../../include/Tile.hpp"

using namespace std;

Tile::Tile(double x, double y, bool isStart, bool isEnd, TileType type)
{
    this->isStart = isStart;
    this->isEnd = isEnd;
    this->isClosed = false;
    this->type = type;
    setStringPath();
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

void Tile::toggleIsClosed()
{
    this->isClosed = !isClosed;
}

bool Tile::isPath()
{
    if (this->type != TileType::Grass)
    {
        return true;
    }
    return false;
}

void Tile::setStringPath()
{
    switch (this->type)
    {
    case TileType::Grass:
        this->tile_string_path = "/images/grass.png";
        break;
    case TileType::Curve:
        this->tile_string_path = "/images/cuve.png";
        break;
    case TileType::FourWays:
        this->tile_string_path = "/images/four_ways.png";
        break;
    case TileType::ThreeWays:
        this->tile_string_path = "/images/three_ways.png";
        break;
    case TileType::Straight:
        this->tile_string_path = "/images/straight.png";
        break;
    }
}