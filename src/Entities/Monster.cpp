#include <iostream>
#include "Monster.hpp"
#include "Position.hpp"

using namespace std;

Monster::Monster(double max_health, double speed, MonsterType type, bool is_boss, bool is_freeze)
{
    this->max_health = max_health;
    this->health_points = max_health;
    this->speed = speed;
    this->path_sprite = path_sprite;
    this->type = type;
    this->is_boss = is_boss;
    this->is_freeze = is_freeze;
    this->is_burning = false;
    this->is_dead = false;
}

Position Monster::getMonsterPosition()
{
    return position;
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
    return this->is_boss;
}

bool Monster::getIsDead()
{
    return this->is_dead;
}

// void Monster::findPathSprite()
// {
//     switch (type)
//     {
//     case MonsterType::Orque:
//         path_sprite = "images/orque6464.png";
//         break;

//     case MonsterType::Meduse:
//         path_sprite = "";

//     case MonsterType::Poseidon:
//         path_sprite = "";

//     case MonsterType::Requin:
//         path_sprite = "";
//     }
// }

void Monster::changeSpeed(double coeff)
{
    speed *= coeff;
}

void Monster::takeDamage(double damage)
{
    health_points -= damage;
    if (health_points <= 0)
    {
        this->is_dead = true;
    }
}

void Monster::toggleFreeze()
{
    is_freeze = !is_freeze;
}
void Monster::toggleBurn()
{
    is_burning = !is_burning;
}