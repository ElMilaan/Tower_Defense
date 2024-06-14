#include <iostream>
#include "Barrage.hpp"
#include "Graph.hpp"
// #include "Map.hpp"

using namespace std;

Barrage::Barrage(GLuint texture)
{
    this->texture = texture;
}

GLuint Barrage::getTexture()
{
    return this->texture;
}

void Barrage::update(double current_time, float delta_time, GLuint barrage_texture, Node &node)
{
    glPushMatrix();
    glScalef(0.4f, 0.4f, 0.4f);
    drawBarrage(barrage_texture, 16.0f, node);
    glPopMatrix();
}
