#include <iostream>
#include "Color.hpp"

using namespace std;

void Color::setColor(const int &r, const int &g, const int &b, const int &t)
{
    this->red = r;
    this->blue = b;
    this->green = g;
    this->transparency = t;
}

bool Color::isEqualTo(Color c)
{
    return this->red == c.red && this->blue == c.blue && this->green == c.green;
}

bool Color::isOut(Color out_color)
{
    return isEqualTo(out_color);
}
bool Color::isIn(Color in_color)
{
    return isEqualTo(in_color);
}
bool Color::isPath(Color path_color)
{
    return isEqualTo(path_color);
}