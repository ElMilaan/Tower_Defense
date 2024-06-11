#include <iostream>
#include "Monster.hpp"
#include "utils.hpp"
#include "Itd.hpp"
#include "Node.hpp"
#include "Draw.hpp"

#include <glm/glm.hpp>

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const string Monster::ITD_FILE = "data/monster.itd";

Monster::Monster(MonsterType type, GLuint texture)
{
    setAttributes(type, texture);
}

MonsterType Monster::getType()
{
    return this->type;
}

glm::vec2 Monster::getPosition()
{
    return {this->x, this->y};
}

double Monster::getMaxHealth()
{
    return this->max_health;
}

double Monster::getHealthPoints()
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

void Monster::changeSpeed(float coeff)
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
    this->current_node_index = 0;
    this->x = 7;
    this->y = 0;
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

void Monster::update(float deltaTime, vector<Node> shortest_path, GLfloat map_size)
{
    if (current_node_index < shortest_path.size() - 1)
    {
        glm::vec2 target_position{shortest_path[current_node_index + 1].getPosition()};
        glm::vec2 direction{glm::normalize(target_position - this->getPosition())};
        this->shift(direction * this->speed * deltaTime);

        glPushMatrix();
        glScalef(0.4f, 0.4f, 0.4f);
        drawMonster(*this, 16.0f);
        glPopMatrix();

        if (getDistanceBetweenTwoPoints(this->getPosition(), target_position) < speed * deltaTime)
        {
            current_node_index++;
        }
    }
}