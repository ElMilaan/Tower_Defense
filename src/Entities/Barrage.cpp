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