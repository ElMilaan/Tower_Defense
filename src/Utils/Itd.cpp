#include <iostream>
#include <vector>
#include "Map.hpp"
#include "Color.hpp"
#include "utils.hpp"
#include "Itd.hpp"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/* -------------------------- MAP -------------------------- */

bool openFile(std::ifstream &file, const std::string &path1, const std::string &path2)
{
    file.open(path1);
    if (!file.is_open())
    {
        file.open(path2);
    }
    return file.is_open();
}

Color ITD::getColorFromItd(vector<string> &split_line)
{
    return {stoi(split_line[1]), stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4])};
}

void ITD::getNodesFromItdFile(vector<string> &split_line, bool const &is_barrage, Map &map)
{
    Node node(stoi(split_line[1]), is_barrage, stof(split_line[2]), stof(split_line[3]));

    if (stoi(split_line[1]) != map.getNbNodes() - 1)
    {
        if (stoi(split_line[1]) == 0)
        {
            node.setStatus(NodeStatus::Start);
        }
        else
        {
            node.setStatus(NodeStatus::Path);
        }
        for (int i{4}; i < split_line.size(); i++)
        {
            node.addNeighbor(stoi(split_line[i]));
        }
    }
    else
    {
        node.setStatus(NodeStatus::End);
    }
    map.addNode(node);
}

void ITD::itdMap(Map &map)
{
    ifstream my_file;

    if (openFile(my_file, ITD::ITD_MAP_1, ITD::ITD_MAP_2))
    {
        string my_line;
        while (getline(my_file, my_line))
        {
            vector<string> split_line = splitString(my_line);

            if (my_line.starts_with("path"))
            {
                map.setColorPath(getColorFromItd(split_line));
            }
            else if (my_line.starts_with("in"))
            {
                map.setColorIn(getColorFromItd(split_line));
            }
            else if (my_line.starts_with("out"))
            {
                map.setColorOut(getColorFromItd(split_line));
            }
            else if (my_line.starts_with("graph"))
            {
                map.setNbNodes(stoi(split_line[1]));
            }
            else if (my_line.starts_with("node"))
            {
                getNodesFromItdFile(split_line, 0, map);
            }
            else if (my_line.starts_with("barrage"))
            {
                getNodesFromItdFile(split_line, 1, map);
            }
        }
    }
    else
    {
        cout << "Couldn't open map file\n";
    }
}

/* -------------------------- MONSTER -------------------------- */

void ITD::itdMonster(string monster_name, Monster &monster)
{
    ifstream my_file;

    if (openFile(my_file, ITD::ITD_MONSTER_1, ITD::ITD_MONSTER_2))
    {
        string my_line;
        while (getline(my_file, my_line))
        {
            vector<string> split_line = splitString(my_line);

            if (my_line.starts_with(monster_name))
            {
                monster.setMaxHealth(stod(split_line[1]));
                monster.setSpeed(stof(split_line[2]));
                monster.setIsBoss(stoi(split_line[3]));
                monster.setReward(stod(split_line[4]));
            }
        }
    }
    else
    {
        cout << "Couldn't open monster file\n";
    }
}

/* -------------------------- WAVE -------------------------- */

void ITD::itdWave(vector<Wave> &waves, unordered_map<MonsterType, GLuint> monster_textures)
{
    ifstream my_file;

    if (openFile(my_file, ITD::ITD_WAVE_1, ITD::ITD_WAVE_2))
    {
        string my_line;
        while (getline(my_file, my_line))
        {
            Wave w{};
            vector<string> split_line = splitString(my_line);

            if (my_line.starts_with("wave"))
            {

                w.setId(stoi(split_line[1]));
                w.setNbMonsters(stoi(split_line[2]));
                w.setIsBossWave(stoi(split_line[3]));
                if (stoi(split_line[3]) == 1)
                {
                    w.addMonster(Monster(MonsterType::Poseidon, monster_textures.at(MonsterType::Poseidon), true));
                }
                else
                {
                    for (int i{0}; i < w.nb_monsters; i++)
                    {
                        (i == w.nb_monsters - 1) ? w.addMonster(createRandomMonster(monster_textures, true)) : w.addMonster(createRandomMonster(monster_textures, false));
                    }
                }
                waves.push_back(w);
            }
        }
    }
    else
    {
        cout << "Couldn't open wave file\n";
    }
}

/* -------------------------- TOWER -------------------------- */

void ITD::itdTower(unordered_map<int, pair<Tower, bool>> &towers, GLuint tower_texture)
{
    ifstream my_file;

    if (openFile(my_file, ITD::ITD_TOWER_1, ITD::ITD_TOWER_2))
    {
        string my_line;
        TowerType type;
        double range;
        double power;
        float attack_speed;
        double cost;
        int tower_id{0};
        while (getline(my_file, my_line))
        {
            vector<string> split_line = splitString(my_line);

            if (my_line.starts_with("range"))
            {
                range = stod(split_line[1]);
            }
            if (my_line.starts_with("power"))
            {
                power = stod(split_line[1]);
            }
            if (my_line.starts_with("cost"))
            {
                cost = stod(split_line[1]);
            }
            if (my_line.starts_with("attack_speed"))
            {
                attack_speed = stof(split_line[1]);
            }
            if (my_line.starts_with("tower"))
            {
                (split_line[3] == "ice") ? type = TowerType::Ice : type = TowerType::Fire;
                Tower t{stof(split_line[1]), stof(split_line[2]), range, power, type, cost, attack_speed, tower_texture};
                towers.insert({tower_id, {t, 0}});
                tower_id++;
            }
        }
    }
    else
    {
        cout << "Couldn't open monster file\n";
    }
}