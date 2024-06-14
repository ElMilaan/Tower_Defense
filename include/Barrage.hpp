#pragma once

#include <iostream>
#include "Map.hpp"
#include "Graph.hpp"
#include "Draw.hpp"

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
    void deploy(Map &map, GLuint barrage_texture);
    void Barrage::update(double current_time, float delta_time, GLuint barrage_texture, Node &node);
};