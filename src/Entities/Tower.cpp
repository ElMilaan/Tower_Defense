#include <iostream>
#include <vector>
#include "Tower.hpp"
#include "Monster.hpp"
#include "Wave.hpp"
#include "utils.hpp"
#include "Draw.hpp"
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
    this->last_shot = 0;
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

bool Tower::isMonsterInRange(Monster monster)
{
    if (getDistanceBetweenTwoPoints({this->x, this->y}, monster.getPosition()) <= range)
    {
        return true;
    }
    return false;
}

void Tower::attack(Monster &monster)
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
    monster.takeDamage(power);
}

void Tower::update(double current_time, Monster &m, GLfloat map_size)
{
    if (current_time - last_shot >= (double)(CADENCE / attack_speed))
    {
        attack(m);
        last_shot = current_time;
        cout << m.getHealthPoints() << endl;
    }
    // glPushMatrix();
    // drawTower(*this, map_size);
    // glPopMatrix();
}
