#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

enum class TileType
{
    Straight,
    Curve,
    FourWays,
    ThreeWays,
    Grass
};

struct Tile
{
    GLfloat x{};
    GLfloat y{};
    GLuint texture{};
    TileType type{};
    GLfloat rotation{};
    bool is_closed{};
    const GLfloat SIZE{1};
};