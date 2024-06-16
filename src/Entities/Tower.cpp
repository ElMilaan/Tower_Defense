#include <iostream>
#include <vector>
#include "Tower.hpp"
#include "Monster.hpp"
#include "utils.hpp"
#include <stack>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Tower::Tower(GLfloat x, GLfloat y, double range, double power, TowerType type, double construction_cost, float attack_speed, GLuint texture)
{
    this->x = x;
    this->y = y;
    this->texture = texture;
    this->range = range;
    this->power = power;
    this->level = 1;
    this->attack_speed = attack_speed;
    this->construction_cost = construction_cost;
    this->type = type;
}

glm::vec2 Tower::getPosition()
{
    return {x, y};
}

GLuint Tower::getTexture()
{
    return texture;
}

void Tower::levelUp(double cost, double bank_sold, GLuint new_texture)
{
    level += 1;
    bank_sold -= cost;
    power *= 2;
    texture = new_texture;
}

void Tower::build(glm::vec2 position)
{
}

void Tower::destruct()
{
}

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

void Tower::attack(Monster &monster)
{

    if (isMonsterInRange(monster))
    {
        switch (type)
        {
        case TowerType::Fire:
            monster.setIsBurn(true);
            break;
        case TowerType::Ice:
            monster.setIsFreeze(true);
            break;
        }
        inflictDamage(monster);
    }
}

void Tower::inflictDamage(Monster &monster)
{
    (monster.getHealthPoints() - power < 0) ? monster.setHealth(0) : monster.setHealth(monster.getHealthPoints() - power);
}