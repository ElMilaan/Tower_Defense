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
    Location location{};
    string tile_path{};
    bool isStart{};
    bool isEnd{};
    bool isClosed{};

public:
    Tile(double x, double y, bool isStart, bool isEnd);
    Location getLocation();
    bool getIsStart();
    bool getIsEnd();
    bool getIsClosed();
    void setLocation(Location loc);
    void toggleIsClosed();
};