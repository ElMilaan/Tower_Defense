#pragma once

#include <iostream>
#include <vector>
#include "Map.hpp"
#include "Color.hpp"
#include "Wave.hpp"
#include "Tower.hpp"
#include "Monster.hpp"

using namespace std;

namespace ITD
{
    /* ------ ITD PATHS ------*/
    const string ITD_MAP_1{"../../data/config_map.itd"};
    const string ITD_MONSTER_1{"../../data/monster.itd"};
    const string ITD_WAVE_1{"../../data/wave.itd"};
    const string ITD_TOWER_1{"../../data/tower.itd"};

    const string ITD_MAP_2{"data/config_map.itd"};
    const string ITD_MONSTER_2{"data/monster.itd"};
    const string ITD_WAVE_2{"data/wave.itd"};
    const string ITD_TOWER_2{"data/tower.itd"};

    /* ------ MAP ------ */

    Color getColorFromItd(vector<string> &split_line);
    void getNodesFromItdFile(vector<string> &split_line, bool const &is_barrage, Map &map);
    void itdMap(Map &map);

    /* ------ MONSTERS ------*/

    void itdMonster(string monster_name, Monster &monster);

    /* ------ WAVES ------*/

    void itdWave(vector<Wave> &waves, unordered_map<MonsterType, GLuint> monster_textures);

    /* ----- TOWERS ------*/

    void itdTower(unordered_map<int, pair<Tower, bool>> &towers, GLuint tower_texture);
}
