#include <iostream>
#include "Position.hpp"
#include "Map.hpp"

using namespace std;

Position::Position()
{
}

Position::Position(double &x, double &y)
{
    this->x = x;
    this->y = y;
}

double Position::getX()
{
    return x;
}

double Position::getY()
{
    return y;
}

bool Position::getIsPath()
{
    return isPath;
}

void Position::setX(double x)
{
    this->x = x;
}

void Position::setY(double y)
{
    this->y = y;
}

void Position::setIsPath(bool isPath)
{
    this->isPath = isPath;
}

MonsterPosition::MonsterPosition()
{
    // Coordonnées de la case de départ
    this->setX(7);
    this->setY(0);
}