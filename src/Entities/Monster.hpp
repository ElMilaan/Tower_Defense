#pragma once

#include <iostream>
#include "Location.hpp"

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
    MonsterLocation location{};

public:
    Monster(double health_points, double speed, MonsterType type, bool isBoss);
    void find_path_sprite();
    void change_speed(float coeff);
    void take_damage(float damage);
    MonsterLocation getMonsterLocation();
    double getMaxHealth();
    double getHealthPoints();
    double getSpeed();
    bool getIsBoss();
    bool getIsDead();
};