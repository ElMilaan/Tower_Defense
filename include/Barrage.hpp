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
    void update(Node node);
    void setNodeId(int node_id);
    int getNodeId();
    Barrage(GLuint texture);
    GLuint getTexture();
};