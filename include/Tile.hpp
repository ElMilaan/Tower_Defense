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

class Tile
{
private:
    static const int SIZE{64};
    string tile_string_path{};
    bool isStart{};
    bool isEnd{};
    bool isClosed{};
    TileType type{};
    GLuint texture{};

public:
    Tile();
    Tile(double x, double y, TileType type);
    bool getIsStart();
    bool getIsEnd();
    bool getIsClosed();
    void toggleIsClosed();
    bool isPath();
    void setTexture(GLuint texture);
};