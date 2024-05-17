#pragma once

#include <iostream>

using namespace std;

class Location
{
private:
    double x{};
    double y{};
    bool isPath{false};

public:
    Location();
    Location(double &x, double &y); // Map map);
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