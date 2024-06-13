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
}

Wave::Wave(int id, unordered_map<MonsterType, GLuint> monster_textures)
{
    this->id = id;
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

// void Wave::update(double inter_time)
// {
//     timeSinceLastSpawn += inter_time;
//     if (timeSinceLastSpawn >= INTER_TIME)
//     {
//         monsters.emplace_back(path, monsterSpeed);
//         timeSinceLastSpawn = 0.0f;
//     }

//     for (auto &monster : monsters)
//     {
//         monster.update(inter_time);
//     }
// }