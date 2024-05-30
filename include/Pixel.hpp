#pragma once

#include <iostream>
#include "Color.hpp"

using namespace std;

enum class PixelStatus
{
    Grass,
    Path,
    In,
    Out
};

struct Pixel
{
    int posX{};
    int posY{};
    Color color{};
    PixelStatus status{};

    void setStatus(Color c, Color in_color, Color path_color, Color out_color);
};

bool operator==(Pixel &p1, Pixel &p2);
bool operator!=(Pixel &p1, Pixel &p2);