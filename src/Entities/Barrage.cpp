#include <iostream>
#include "Barrage.hpp"
#include "Graph.hpp"

using namespace std;

Barrage::Barrage(GLuint texture)
{
    this->texture = texture;
}

int Barrage::getNodeId()
{
    return this->node_id;
}

void Barrage::setNodeId(int node_id)
{
    this->node_id = node_id;
}

GLuint Barrage::getTexture()
{
    return this->texture;
}

void Barrage::update(Node node)
{
    glPushMatrix();
    glScalef(0.4f, 0.4f, 0.4f);
    drawBarrage(this->texture, 16.0f, node);
    glPopMatrix();
}
