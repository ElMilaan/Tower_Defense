#pragma once

#include <iostream>
#include "Position.hpp"

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
    string path_sprite{};
    bool isBoss{};
    bool isDead{};
    MonsterPosition position{};

public:
    Monster(double health_points, double speed, MonsterType type, bool isBoss);
    void find_path_sprite();
    void change_speed(double coeff);
    void take_damage(double damage);
    MonsterPosition getMonsterPosition();
    double getMaxHealth();
    double getHealthPoints();
    double getSpeed();
    bool getIsBoss();
    bool getIsDead();
};