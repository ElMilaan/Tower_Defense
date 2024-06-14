#pragma once

#include <iostream>
#include "Graph.hpp"
#include "Draw.hpp"

using namespace std;

class Barrage
{
private:
    GLuint texture{};

public:
    Barrage(GLuint texture);
    void update(double current_time, float delta_time, GLuint barrage_texture, Node &node);
    GLuint getTexture();
};