#pragma once

#include <iostream>
// #include "Map.hpp"
#include "Graph.hpp"
#include "Draw.hpp"

using namespace std;

class Barrage
{
private:
    GLuint texture{};

public:
    Barrage(GLuint texture);
    GLuint getTexture();
};