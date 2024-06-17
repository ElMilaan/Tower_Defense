#pragma once

#include <iostream>
#include <vector>
#include "Monster.hpp"
#include <unordered_map>

using namespace std;

struct Wave
{
    int id{};
    int nb_monsters;
    vector<Monster> monsters{};
    vector<Monster> monsters_to_update{};
    bool is_boss_wave{};
    double last_spawn{};
    int current_monster_index{};

    double const INTER_TIME{2};

    Wave();
    Wave(int id, unordered_map<MonsterType, GLuint> monster_textures);

    void setId(int id);
    void setNbMonsters(int nb_monsters);
    void setIsBossWave(bool is_boss_wave);
    void addMonster(Monster m);

    void update(double current_time, float delta_time, vector<Node> shortest_path, GLfloat map_size, bool &launch_wave, int &current_wave, vector<GLuint> &game_life);

    void display();
    void launchAttackOnMonster(int monster_index, double power, bool freeze, bool burn);
};

Monster createRandomMonster(unordered_map<MonsterType, GLuint> monster_textures, bool is_last);