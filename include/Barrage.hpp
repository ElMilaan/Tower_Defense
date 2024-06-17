#pragma once

#include <iostream>
#include "Graph.hpp"
#include "Draw.hpp"

using namespace std;

class Barrage
{
private:
    GLuint texture{};
    int node_id{};

public:
    const double COST{30};
    void update(Node node);
    void setNodeId(int node_id);
    int getNodeId();
    Barrage(GLuint texture);
    void update(double current_time, float delta_time, GLuint barrage_texture, Node &node);
    GLuint getTexture();
};