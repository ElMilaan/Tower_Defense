#include <iostream>
#include "Barrage.hpp"
#include "Graph.hpp"

using namespace std;

int Barrage::getNodeId()
{
    return node_id;
}

string Barrage::getSpritePath()
{
    return sprite_path;
}

void Barrage::setNodeId(int id)
{
    node_id = id;
}