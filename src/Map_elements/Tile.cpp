#include <iostream>
#include "Tile.hpp"

using namespace std;

Tile::Tile()
{
}

Tile::Tile(double x, double y, TileType type)
{
    this->isClosed = false;
    this->type = type;
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

void Tile::setTexture(GLuint texture)
{
    this->texture = texture;
}