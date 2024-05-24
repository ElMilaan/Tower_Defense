#pragma once

#include <iostream>
#include <vector>
#include "Tile.hpp"
#include "Graph.hpp"

using namespace std;

class Map
{
private:
    static const int PIXELS_DIMENSION{1024};
    static const int TILES_DIMENSION{64};
    vector<vector<Tile>> tiles{};
    Graph::WeightedGraph graph{};

public:
    Map();
    vector<vector<Tile>> getTiles();
    Graph::WeightedGraph getGraph();
    void addTile(Tile tile);
    Tile getTile(size_t x, size_t y);
};