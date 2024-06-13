#pragma once

#include <iostream>
#include "Graph.hpp"
#include "Map.hpp"

using namespace std;

class Barrage
{
private:
    int node_id;
    string sprite_path{"images/barrage6464.png"};

public:
    int getNodeId();
    string getSpritePath();
    void setNodeId(int id);
    // void deploy(Map &map);
};