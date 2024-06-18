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
    float min_speed{};
    float max_speed{};
    MonsterType type{};
    GLuint texture{};
    bool is_boss{};
    bool is_dead{};
    bool is_moving{};
    bool is_freeze{};
    bool is_burn{};
    int current_node_index{};
    bool is_last_of_wave{};
    double reward{};
    double time_is_freeze{};

public:
    static const int ALTERATION_DURATION{3};
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
    double getReward();
    bool getIsFreeze();
    double getTimeIsFreeze();

    void shift(glm::vec2 deplacement);

    void setMaxHealth(double max_health);
    void setSpeed(float speed);
    void setIsBoss(bool is_boss);
    void setIsLast();
    void setHealth(float new_health);
    void setIsBurn(bool is_burn);
    void setIsFreeze(bool is_freeze, double current_time);
    void setReward(double reward);

    void changeSpeed(float coeff);
    void takeDamage(double damage);
    void setAttributes(MonsterType type, GLuint texture);
    void freezing(double current_time, double start_freeze);

    void update(float deltaTime, vector<Node> shortest_path, GLfloat map_size);

    void display();
};

string monsterTypeToString(MonsterType type);