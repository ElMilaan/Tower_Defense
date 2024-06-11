#pragma once

#include <iostream>
#include <vector>
#include "Monster.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;

enum class TowerType
{
    Fire,
    Ice
};

class Tower
{
private:
    GLfloat x;
    GLfloat y;
    double range{};
    double damage{};
    double attack_speed{};
    double construction_cost{};
    double level{};
    TowerType type{};
    string path_sprite{};

public:
    Tower(GLfloat x, GLfloat y, double range, double damage, double level, TowerType type, double construction_cost, double attack_speed); // constructor
    void findPathSprite();
    void levelUp(double cost, double bank_sold); // tous les levels up valent le meme prix ? sinon il faut faire une autre fonction
    void build(glm::vec2 position);
    void destruct();
    void attack(Monster monster);
    bool isMonsterInRange(Monster monster);
};
