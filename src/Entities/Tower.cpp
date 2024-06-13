#include <iostream>
#include <vector>
#include "Tower.hpp"
#include "Monster.hpp"
#include "utils.hpp"
#include <stack>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Tower::Tower(GLfloat x, GLfloat y, double range, double damage, double level, TowerType type, double construction_cost, double attack_speed)
{
    this->x = x;
    this->y = y;
    this->range = range;
    this->damage = damage;
    this->level = level;
    this->attack_speed = attack_speed;
    this->construction_cost = construction_cost;
    this->type = type;
    this->path_sprite = path_sprite;
}

void Tower::findPathSprite()
{
    switch (type)
    {
    case TowerType::Fire:
        path_sprite = "";
        break;
    case TowerType::Ice:
        path_sprite = "";
        break;

    default:
        break;
    }
}

void Tower::levelUp(double cost, double bank_sold)
{
    level += 1;
    path_sprite = "";
    bank_sold -= cost;
}

void Tower::build(glm::vec2 position)
{
}

void Tower::destruct()
{
}

// update
bool Tower::isMonsterInRange(Monster monster)
{
    if (getDistanceBetweenTwoPoints({this->x, this->y}, monster.getPosition()) < range)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Tower::attack(Monster monster)
{
    if (isMonsterInRange(monster))
    {
        switch (type)
        {
        case TowerType::Fire:

            break;
        case TowerType::Ice:
            break;
        }
    }
}