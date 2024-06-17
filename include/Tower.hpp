#pragma once

#include <iostream>
#include <vector>
#include "Monster.hpp"
#include "Wave.hpp"

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
    double last_shot{};
    TowerType type{};

public:
    const vector<float> COSTS{50, 100, 200}; // Couts des niveaux (et de la premiere construction)
    const float CADENCE{5.0f};
    Tower(GLfloat x, GLfloat y, double range, double power, TowerType type, double construction_cost, float attack_speed, GLuint texture); // constructor
    glm::vec2 getPosition();
    GLuint getTexture();
    void levelUp(double cost, double bank_sold, GLuint new_texture); // tous les levels up valent le meme prix ? sinon il faut faire une autre fonction
    void attack(Monster &monster);
    bool isMonsterInRange(Monster monster);
    void update(double current_time, Monster &m);
};
