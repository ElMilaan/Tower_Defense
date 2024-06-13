#pragma once

#include <iostream>
#include <vector>
#include "Node.hpp"
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
    GLfloat x;
    GLfloat y;
    double max_health{};
    double health_points{};
    float speed{};
    MonsterType type{};
    GLuint texture{};
    bool is_boss{};
    bool is_dead{};
    bool is_moving{};
    bool is_freeze{};
    bool is_burning{};
    int current_node_index{};

public:
    static const string ITD_FILE;
    Monster();
    Monster(MonsterType type, GLuint texture);
    glm::vec2 getPosition();
    double getMaxHealth();
    double getHealthPoints();
    float getSpeed();
    MonsterType getType();
    GLuint getTexture();
    bool getIsBoss();
    bool getIsDead();

    void shift(glm::vec2 deplacement);

    void setMaxHealth(double max_health);
    void setSpeed(float speed);
    void setIsBoss(bool is_boss);

    void changeSpeed(float coeff);
    void takeDamage(double damage);
    void toggleFreeze();
    void toggleBurn();
    void setAttributes(MonsterType type, GLuint texture);

    void update(float deltaTime, vector<Node> shortest_path, GLfloat map_size);

    void display();
};

string monsterTypeToString(MonsterType type);