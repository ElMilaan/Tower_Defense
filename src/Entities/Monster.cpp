#include <iostream>
#include "Monster.hpp"
#include "Position.hpp"

using namespace std;

Monster::Monster(double max_health, double speed, MonsterType type, bool isBoss)
{
    this->max_health = max_health;
    this->health_points = max_health;
    this->speed = speed;
    this->path_sprite = path_sprite;
    this->type = type;
    this->isBoss = isBoss;
    this->isDead = false;
}

MonsterPosition Monster::getMonsterPosition()
{
    return position;
}

void Monster::find_path_sprite()
{
    switch (type)
    {
    case MonsterType::Orque:
        path_sprite = "images/orque6464.png";
        break;

    case MonsterType::Meduse:
        path_sprite = "";

    case MonsterType::Poseidon:
        path_sprite = "";

    case MonsterType::Requin:
        path_sprite = "";

    default:
        break;
    }
}

void Monster::change_speed(double coeff)
{
    speed *= coeff;
}

void Monster::take_damage(double damage)
{
    health_points -= damage;
    if (health_points <= 0)
    {
        this->isDead = true;
    }
}

double Monster::getMaxHealth()
{
    return this->max_health;
}

double Monster::getHealthPoints()
{
    return this->health_points;
}

double Monster::getSpeed()
{
    return this->speed;
}

bool Monster::getIsBoss()
{
    return this->isBoss;
}

bool Monster::getIsDead()
{
    return this->isDead;
}