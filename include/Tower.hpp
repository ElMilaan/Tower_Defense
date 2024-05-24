#pragma once

#include <iostream>
#include <vector>
#include "Monster.hpp"

using namespace std;

enum class TowerType
{
    Fire,
    Ice
};

class Tower
{
public:
    Tower(double range, double damage, double level, TowerType type, double construction_cost, double attack_speed); // constructor
    void find_path_sprite();
    void level_up(double cost, double bank_sold); // tous les levels up valent le meme prix ? sinon il faut faire une autre fonction
    void build(pair<double, double> position);
    void destruct();
    void attack(Monster monster);
    bool is_Monster_in_range(Monster monster);

private:
    double range{};
    double damage{};
    double attack_speed{};
    double construction_cost{};
    double level{};
    TowerType type{};
    string path_sprite{};
};
