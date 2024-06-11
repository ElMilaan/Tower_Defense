#pragma once

#include <iostream>
#include "Position.hpp"
#include "GlFW/glfw3.h"

using namespace std;

enum class MonsterType
{
    Orque = 0,
    Meduse = 1,
    Requin = 2,
    Poseidon = 3
};

class Monster
{

private:
    double max_health{};
    double health_points{};
    double speed{};
    MonsterType type{};
    GLuint texture{};
    bool is_boss{};
    bool is_dead{};
    bool is_moving{};
    bool is_freeze{};
    bool is_burning{};
    Position position{};

public:
    static const string ITD_FILE;
    Monster(MonsterType type, GLuint texture);
    Position getMonsterPosition();
    double getMaxHealth();
    double getHealthPoints();
    double getSpeed();
    MonsterType getType();
    GLuint getTexture();
    bool getIsBoss();
    bool getIsDead();

    void setMaxHealth(double max_health);
    void setSpeed(double speed);
    void setIsBoss(bool is_boss);

    void changeSpeed(double coeff);
    void takeDamage(double damage);
    void toggleFreeze();
    void toggleBurn();
    void setAttributes(MonsterType type, GLuint texture);
    // void itdMonster(string monster);

    void display();
};

string monsterTypeToString(MonsterType type);