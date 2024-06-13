#pragma once

#include <iostream>
#include <vector>
#include "Monster.hpp"
#include <unordered_map>

using namespace std;

class Wave
{
private:
    int id{};
    int nb_monsters;
    vector<Monster> monsters{};
    vector<Monster> monsters_to_update{};
    bool is_boss_wave{};
    double last_spawn{};
    int current_monster_index{};

public:
    double const INTER_TIME{6};

    Wave();
    Wave(int id, unordered_map<MonsterType, GLuint> monster_textures);

    int getId();
    int getNbMonsters();
    vector<Monster> getMonsters();

    void setId(int id);
    void setNbMonsters(int nb_monsters);
    void setIsBossWave(bool is_boss_wave);
    void addMonster(Monster m);

    void update(double current_time, float delta_time, vector<Node> shortest_path, GLfloat map_size);

    void display();
};

Monster createRandomMonster(unordered_map<MonsterType, GLuint> monster_textures);