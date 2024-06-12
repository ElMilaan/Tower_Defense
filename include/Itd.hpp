#pragma once

#include <iostream>
#include <vector>
#include "Map.hpp"
#include "Color.hpp"
#include "Wave.hpp"

using namespace std;

namespace ITD
{
    /* ------ ITD PATHS ------*/
    const string ITD_MAP{"../../data/config_map.itd"};
    const string ITD_MONSTER{"../../data/monster.itd"};
    const string ITD_WAVE{"../../data/wave.itd"};

    /* ------ MAP ------ */

    Color getColorFromItd(vector<string> &split_line);
    void getNodesFromItdFile(vector<string> &split_line, bool const &is_barrage, Map &map);
    void itdMap(Map &map);

    /* ------ MONSTERS ------*/

    void itdMonster(string monster_name, Monster &monster);

    /* ------ WAVES ------*/

    void itdWave(vector<Wave> &waves, unordered_map<MonsterType, GLuint> monster_textures);
}
