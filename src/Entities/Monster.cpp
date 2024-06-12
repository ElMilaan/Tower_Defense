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
    this->y = 0.5;
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
    // Pour matcher avec le centre des textures du monstre et de la tile
    float mid_texture{0.5};
    float mid_tile{0.5};

    // Limite a ne pas dépasser pour ne pas sortir de la map
    GLfloat const LIMIT{map_size - 0.1f};

    glm::vec2 target_position{shortest_path[current_node_index + 1].getPosition().x, shortest_path[current_node_index + 1].getPosition().y + mid_texture + mid_tile};

    // cout << target.getPosition().x << " , " << target.getPosition().y << endl;

    glm::vec2 go{glm::normalize(target_position - this->getPosition())};

    if (this->getPosition().y < LIMIT)
    {
        if (abs(this->getPosition().x - target_position.x) > abs(this->getPosition().y - target_position.y))
        {
            if (round(target_position.x * 10) / 10.0f != round(this->getPosition().x * 10) / 10.0f)
            {
                this->shift({go.x * deltaTime * speed, 0});
                cout << target_position.x << " , " << this->getPosition().x << endl;
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
                cout << target_position.y << " , " << this->getPosition().y << endl;
            }
            else
            {
                current_node_index++;
                this->y = target_position.y;
            }
        }
        glPushMatrix();
        glScalef(0.4f, 0.4f, 0.4f);
        drawMonster(*this, 16.0f);
        glPopMatrix();
    }
}