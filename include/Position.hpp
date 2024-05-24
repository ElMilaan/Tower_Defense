#pragma once

#include <iostream>
#include "Map.hpp"

using namespace std;

class Position
{
private:
    double x{};
    double y{};
    bool isPath{false};

public:
    Position();
    Position(double &x, double &y);
    double getX();
    double getY();
    bool getIsPath();
    void setX(double x);
    void setY(double y);
    void setIsPath(bool isWay);
};

class MonsterPosition : Position
{
public:
    MonsterPosition();
};