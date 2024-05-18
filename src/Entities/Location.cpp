#include <iostream>
#include "Location.hpp"
#include "../Map_elements/Map.hpp"

using namespace std;

Location::Location()
{
}

Location::Location(double &x, double &y)
{
    this->x = x;
    this->y = y;
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
    // Coordonnées de la case de départ
    this->setX(7);
    this->setY(0);
}