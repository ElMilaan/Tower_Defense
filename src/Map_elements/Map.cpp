#include <iostream>
#include <vector>
#include "Tile.hpp"
#include "Map.hpp"

using namespace std;

Map::Map()
{
}

vector<vector<Tile>> Map::getTiles()
{
    return this->tiles;
}

void Map::addTile(Tile tile)
{
    size_t size{this->tiles.size()};
    if (size <= 16 && this->tiles[size].size() < 16)
    {
        tiles[size].push_back(tile);
    }
}