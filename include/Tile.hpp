#pragma once

#include <iostream>
#include "Position.hpp"
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
    static const int SIZE{64};
    GLuint texture{};
    TileType type{};
    int rotation{};
    bool isClosed{};
};