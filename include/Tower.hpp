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
    GLfloat x{};
    GLfloat y{};
    GLuint texture{};
    double range{};
    double power{};
    float attack_speed{};
    double construction_cost{};
    double level{};
    TowerType type{};

public:
    Tower(GLfloat x, GLfloat y, double range, double power, TowerType type, double construction_cost, float attack_speed, GLuint texture); // constructor
    glm::vec2 getPosition();
    GLuint getTexture();
    void levelUp(double cost, double bank_sold, GLuint new_texture); // tous les levels up valent le meme prix ? sinon il faut faire une autre fonction
    void build(glm::vec2 position);
    void destruct();
    void attack(Monster &monster);
    void inflictDamage(Monster &monster);
    bool isMonsterInRange(Monster monster);
};
