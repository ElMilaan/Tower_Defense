#pragma once

#include <iostream>
#include "Location.hpp"

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

public:
    Tile(double x, double y, bool isStart, bool isEnd, TileType type);
    bool getIsStart();
    bool getIsEnd();
    bool getIsClosed();
    void toggleIsClosed();
    bool isPath();
    void setStringPath();
};