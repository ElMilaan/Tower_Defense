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
    float max_health{};
    float health_points{};
    float speed{};
    MonsterType type{};
    GLuint texture{};
    bool is_boss{};
    bool is_dead{};
    bool is_moving{};
    bool is_freeze{};
    bool is_burning{};
    int current_node_index{};
    bool is_last_of_wave{};

public:
    static const string ITD_FILE;
    Monster();
    Monster(MonsterType type, GLuint texture, bool is_last);
    glm::vec2 getPosition();
    float getMaxHealth();
    float getHealthPoints();
    float getSpeed();
    MonsterType getType();
    GLuint getTexture();
    bool getIsBoss();
    bool getIsDead();
    bool getIsLast();

    void shift(glm::vec2 deplacement);

    void setMaxHealth(double max_health);
    void setSpeed(float speed);
    void setIsBoss(bool is_boss);
    void setIsLast();

    void changeSpeed(float coeff);
    void takeDamage(double damage);
    void toggleFreeze();
    void toggleBurn();
    void setAttributes(MonsterType type, GLuint texture);

    void update(float deltaTime, vector<Node> shortest_path, GLfloat map_size, bool &launch_wave, int &current_wave);

    void display();
};

string monsterTypeToString(MonsterType type);