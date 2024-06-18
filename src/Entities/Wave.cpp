#include <iostream>
#include <vector>
#include "Monster.hpp"
#include "Wave.hpp"
#include "utils.hpp"
#include "Bank.hpp"

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

Monster createRandomMonster(unordered_map<MonsterType, GLuint> monster_textures, bool is_last)
{
    MonsterType randomType{static_cast<MonsterType>(random_int(0, sizeof(MonsterType) - 1))};
    GLuint texture{monster_textures.at(randomType)};
    return Monster(randomType, texture, is_last);
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

void Wave::update(double current_time, float delta_time, vector<Node> shortest_path, GLfloat map_size, bool &launch_wave, int &current_wave, vector<GLuint> &game_life, Bank &bank)
{
    if (current_monster_index < monsters.size())
    {
        if (current_time - last_spawn >= INTER_TIME)
        {
            monsters_to_update.push_back(monsters[current_monster_index]);
            last_spawn = current_time;

            current_monster_index++;
        }
    }
    GLfloat const LIMIT{map_size - 0.1f};
    for (int i{0}; i < monsters_to_update.size(); i++)
    {
        if (monsters_to_update[i].getPosition().y < LIMIT && !monsters_to_update[i].getIsDead())
        {
            if (monsters_to_update[i].getIsFreeze())
            {
                monsters_to_update[i].freezing(current_time, monsters_to_update[i].getTimeIsFreeze());
            }
            monsters_to_update[i].update(delta_time, shortest_path, map_size);
        }
        else
        {
            if (!monsters_to_update[i].getIsDead())
            {
                game_life.pop_back();
            }
            else
            {
                bank.addMoney(monsters_to_update[i].getReward());
            }
            if (monsters_to_update[i].getIsLast())
            {
                launch_wave = false;
                current_wave++;
            }
            monsters_to_update.erase(monsters_to_update.begin() + i);
        }
    }
}
