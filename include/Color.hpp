#pragma once
#include <iostream>

using namespace std;

struct Color
{
    int red;
    int green;
    int blue;
    int transparency;

    void setColor(const int &r, const int &g, const int &b, const int &t);
    bool isEqualTo(Color c);
    bool isOut(Color out_color);
    bool isIn(Color in_color);
    bool isPath(Color path_color);
};

bool operator==(Color const &c1, Color const &c2);