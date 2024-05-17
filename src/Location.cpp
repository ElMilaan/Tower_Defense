#include <iostream>
#include "Location.hpp"

using namespace std;

Location::Location()
{
}

Location::Location(double &x, double &y) // Map map)
{
    this->x = x;
    this->y = y;
    // if (map.isWay(x, y))
    // {
    //     isPath = true;
    // }
    // else
    // {
    //     isPath = false;
    // }
}

double Location::getX()
{
    return x;
}

double Location::getY()
{
    return y;
}

bool Location::getIsPath()
{
    return isPath;
}

void Location::setX(double x)
{
    this->x = x;
}

void Location::setY(double Y)
{
    this->y = y;
}

void Location::setIsPath(bool isPath)
{
    this->isPath = isPath;
}

MonsterLocation::MonsterLocation()
{
    this->setX(7);
    this->setY(0);
}