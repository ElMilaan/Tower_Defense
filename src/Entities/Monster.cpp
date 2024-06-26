#include <iostream>
#include "Monster.hpp"
#include "utils.hpp"
#include "Itd.hpp"
#include "Node.hpp"
#include "Draw.hpp"

#include <cmath>
#include <glm/glm.hpp>

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Monster::Monster(MonsterType type, GLuint texture, bool is_last)
{
    setAttributes(type, texture);
    this->is_last_of_wave = is_last;
    this->max_speed = speed;
    this->min_speed = speed * 0.6f;
}

MonsterType Monster::getType()
{
    return this->type;
}

glm::vec2 Monster::getPosition()
{
    return {this->x, this->y};
}

float Monster::getMaxHealth()
{
    return this->max_health;
}

float Monster::getHealthPoints()
{
    return this->health_points;
}

float Monster::getSpeed()
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

bool Monster::getIsLast()
{
    return this->is_last_of_wave;
}

double Monster::getReward()
{
    return this->reward;
}

bool Monster::getIsFreeze()
{
    return this->is_freeze;
}

double Monster::getTimeIsFreeze()
{
    return this->time_is_freeze;
}

void Monster::shift(glm::vec2 deplacement)
{
    this->x += deplacement.x;
    this->y += deplacement.y;
}

void Monster::setMaxHealth(double max_health)
{
    this->max_health = max_health;
}
void Monster::setSpeed(float speed)
{
    this->speed = speed;
}
void Monster::setIsBoss(bool is_boss)
{
    this->is_boss = is_boss;
}

void Monster::setIsLast()
{
    this->is_last_of_wave = true;
}

void Monster::setIsBurn(bool is_burn)
{
    this->is_burn = is_burn;
}

void Monster::setIsFreeze(bool is_freeze, double current_time)
{
    this->is_freeze = is_freeze;
    this->time_is_freeze = current_time;
}

void Monster::setHealth(float new_health)
{
    this->health_points = new_health;
}

void Monster::setReward(double reward)
{
    this->reward = reward;
}

void Monster::changeSpeed(float coeff)
{
    speed *= coeff;
}

void Monster::takeDamage(double damage)
{
    health_points -= float(damage);
    if (health_points <= 0)
    {
        this->is_dead = true;
    }
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
    this->is_burn = false;
    this->is_freeze = false;
    this->is_dead = false;
    this->health_points = this->max_health;
    this->current_node_index = 0;
    this->x = 7;
    this->y = 0.5;
}

void Monster::freezing(double current_time, double start_freeze)
{
    if (current_time - start_freeze < ALTERATION_DURATION)
    {
        this->speed = min_speed;
    }
    else
    {
        this->speed = max_speed;
    }
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
    }
    return "Requin";
}

void Monster::update(float deltaTime, vector<Node> shortest_path, GLfloat map_size)
{
    // Pour matcher avec le centre des textures du monstre et de la tile
    float mid_texture{0.5};
    float mid_tile{0.5};

    // Limite a ne pas dépasser pour ne pas sortir de la map
    GLfloat const LIMIT{map_size - 0.1f};

    glm::vec2 target_position{shortest_path[current_node_index + 1].getPosition().x, shortest_path[current_node_index + 1].getPosition().y + mid_texture + mid_tile};

    glm::vec2 go{glm::normalize(target_position - this->getPosition())};

    if (!is_dead)
    {
        if (abs(this->getPosition().x - target_position.x) > abs(this->getPosition().y - target_position.y))
        {
            if (round(target_position.x * 10) / 10.0f != round(this->getPosition().x * 10) / 10.0f)
            {
                this->shift({go.x * deltaTime * speed, 0});
            }
            else
            {
                current_node_index++;
                this->x = target_position.x;
            }
        }
        else
        {
            if (round(target_position.y * 10) / 10.f != round(this->getPosition().y * 10) / 10.f)
            {
                this->shift({0, go.y * deltaTime * speed});
            }
            else
            {
                current_node_index++;
                this->y = target_position.y;
            }
        }
        glPushMatrix();
        drawMonster(*this, map_size);
        glPopMatrix();
    }
}