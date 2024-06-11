#include <iostream>
#include "Monster.hpp"
#include "Position.hpp"
#include "utils.hpp"
#include "Itd.hpp"

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const string Monster::ITD_FILE = "data/monster.itd";

Monster::Monster(MonsterType type, GLuint texture)
{
    setAttributes(type, texture);
}

Position Monster::getMonsterPosition()
{
    return position;
}

MonsterType Monster::getType()
{
    return this->type;
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

GLuint Monster::getTexture()
{
    return this->texture;
}

bool Monster::getIsBoss()
{
    return this->is_boss;
}

bool Monster::getIsDead()
{
    return this->is_dead;
}

void Monster::setMaxHealth(double max_health)
{
    this->max_health = max_health;
}
void Monster::setSpeed(double speed)
{
    this->speed = speed;
}
void Monster::setIsBoss(bool is_boss)
{
    this->is_boss = is_boss;
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

void Monster::setAttributes(MonsterType type, GLuint texture)
{
    switch (type)
    {
    case MonsterType::Meduse:
        ITD::itdMonster("meduse", *this);
        this->type = MonsterType::Meduse;
        this->texture = texture;
        break;
    case MonsterType::Orque:
        ITD::itdMonster("orque", *this);
        this->type = MonsterType::Orque;
        this->texture = texture;
        break;
    case MonsterType::Requin:
        ITD::itdMonster("requin", *this);
        this->type = MonsterType::Requin;
        this->texture = texture;
        break;
    case MonsterType::Poseidon:
        ITD::itdMonster("poseidon", *this);
        this->type = MonsterType::Poseidon;
        this->texture = texture;
        break;
    }
    this->is_moving = true;
    this->is_burning = false;
    this->is_dead = false;
    this->health_points = this->max_health;
}

void Monster::display()
{
    cout << monsterTypeToString(type) << "( MaxHealth=" << this->max_health << ", Speed=" << this->speed << ", Boss=";
    (is_boss) ? cout << "oui )" : cout << "non )";
    cout << endl;
}

string monsterTypeToString(MonsterType type)
{
    switch (type)
    {
    case MonsterType::Meduse:
        return "Meduse";
    case MonsterType::Orque:
        return "Orque";
    case MonsterType::Poseidon:
        return "Poseidon";
    case MonsterType::Requin:
        return "Requin";
    }
}