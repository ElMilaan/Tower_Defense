#pragma once

#include <iostream>
#include "../Map_elements/Map.hpp"

using namespace std;

class Location
{
private:
    double x{};
    double y{};
    bool isPath{false};

public:
    Location();
    Location(double &x, double &y);
    double getX();
    double getY();
    bool getIsPath();
    void setX(double x);
    void setY(double y);
    void setIsPath(bool isWay);
};

class MonsterLocation : Location
{
public:
    MonsterLocation();
};