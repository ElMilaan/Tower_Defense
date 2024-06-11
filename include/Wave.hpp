#pragma once

#include <iostream>
#include <vector>
#include "Position.hpp"
#include "Monster.hpp"
#include <unordered_map>

using namespace std;

class Wave
{
private:
    int id{};
    int nb_monsters;
    vector<Monster> monsters{};
    bool is_boss_wave{};

public:
    double const INTER_TIME{1};

    Wave();
    Wave(int id, unordered_map<MonsterType, GLuint> monster_textures);

    int getId();
    int getNbMonsters();
    vector<Monster> getMonsters();

    void setId(int id);
    void setNbMonsters(int nb_monsters);
    void setIsBossWave(bool is_boss_wave);
    void addMonster(Monster m);

    void display();
};

Monster createRandomMonster(unordered_map<MonsterType, GLuint> monster_textures);