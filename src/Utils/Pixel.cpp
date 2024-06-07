#include <iostream>
#include "Pixel.hpp"
#include "Color.hpp"

void Pixel::setStatus(Color c, Color in_color, Color path_color, Color out_color)
{
    if (c.isIn(in_color))
    {
        status = PixelStatus::In;
    }
    else if (c.isPath(path_color))
    {
        status = PixelStatus::Path;
    }
    else if (c.isOut(out_color))
    {
        status = PixelStatus::Out;
    }
    else
    {
        status = PixelStatus::Grass;
    }
}

bool operator==(Pixel &p1, Pixel &p2)
{
    return p1.posX == p2.posX && p1.posY == p2.posY;
}

bool operator!=(Pixel &p1, Pixel &p2)
{
    return !(p1 == p2);
}