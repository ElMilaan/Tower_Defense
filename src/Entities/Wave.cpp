#include <iostream>
#include <vector>
#include "Monster.hpp"
#include "Wave.hpp"
#include "utils.hpp"

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Wave::Wave()
{
    this->last_spawn = 0;
    this->current_monster_index = 0;
}

Wave::Wave(int id, unordered_map<MonsterType, GLuint> monster_textures)
{
    this->id = id;
    this->last_spawn = 0;
    this->current_monster_index = 0;
}
int Wave::getId()
{
    return this->id;
}
int Wave::getNbMonsters()
{
    return this->nb_monsters;
}
vector<Monster> Wave::getMonsters()
{
    return this->monsters;
}

void Wave::setId(int id)
{
    this->id = id;
}
void Wave::setNbMonsters(int nb_monsters)
{
    this->nb_monsters = nb_monsters;
}
void Wave::setIsBossWave(bool is_boss_wave)
{
    this->is_boss_wave = is_boss_wave;
}

void Wave::addMonster(Monster m)
{
    this->monsters.push_back(m);
}

Monster createRandomMonster(unordered_map<MonsterType, GLuint> monster_textures)
{
    MonsterType randomType{static_cast<MonsterType>(random_int(0, sizeof(MonsterType) - 1))};
    GLuint texture{monster_textures.at(randomType)};
    return Monster(randomType, texture);
}

void Wave::display()
{
    cout << "Wave " << this->id << " : {" << endl;
    for (Monster m : monsters)
    {
        m.display();
    }
    cout << "}" << endl;
}

void Wave::update(double current_time, float delta_time, vector<Node> shortest_path, GLfloat map_size)
{
    if (current_time - last_spawn >= INTER_TIME && current_monster_index < monsters.size())
    {
        monsters_to_update.push_back(monsters[current_monster_index]);
        last_spawn = current_time;

        current_monster_index++;
    }
    for (Monster m : monsters_to_update)
    {
        m.update(delta_time, shortest_path, map_size);
    }
}