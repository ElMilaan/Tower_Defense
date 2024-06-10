#include <iostream>
#include "Monster.hpp"
#include "Position.hpp"
#include "utils.hpp"

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const string Monster::ITD_FILE = "data/monster.itd";

Monster::Monster(MonsterType type, bool is_freeze)
{
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

void Monster::setAttributes(MonsterType type)
{
    switch (type)
    {
    case MonsterType::Meduse:
        this->max_health = max_health;
        this->health_points = max_health;
        this->speed = speed;
        this->type = MonsterType::Meduse;
        this->is_boss = is_boss;
        this->is_freeze = is_freeze;
        break;
    case MonsterType::Orque:
        break;
    case MonsterType::Requin:
        break;
    case MonsterType::Poseidon:
        break;
    }
    this->is_moving = true;
    this->is_burning = false;
    this->is_dead = false;
}

void Monster::itdMonster()
{
    ifstream my_file;

    my_file.open(this->ITD_FILE);

    string my_line;

    if (my_file.is_open())
    {
        while (my_file)
        {
            getline(my_file, my_line);
            vector<string> split_line = splitString(my_line);

            if (my_line.starts_with("meduse"))
            {
            }
        }
    }
    else
    {
        cout << "Couldn't open file\n";
    }
}