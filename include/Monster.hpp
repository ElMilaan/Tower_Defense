#pragma once

#include <iostream>
#include "Position.hpp"
#include "GlFW/glfw3.h"

using namespace std;

enum class MonsterType
{
    Orque,
    Meduse,
    Poseidon,
    Requin,
};

class Monster
{

private:
    double max_health{};
    double health_points{};
    double speed{};
    MonsterType type{};
    bool is_boss{};
    bool is_dead{};
    bool is_moving{};
    bool is_freeze{};
    bool is_burning{};
    Position position{};

public:
    static const string ITD_FILE;
    Monster(MonsterType type, bool is_freeze);
    Position getMonsterPosition();
    double getMaxHealth();
    double getHealthPoints();
    double getSpeed();
    bool getIsBoss();
    bool getIsDead();
    void changeSpeed(double coeff);
    void takeDamage(double damage);
    void toggleFreeze();
    void toggleBurn();
    void setAttributes(MonsterType type);
    void itdMonster();
};