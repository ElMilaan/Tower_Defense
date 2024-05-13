// #include <iostream>
// #include "Monster.hpp"

// using namespace std;

// Monster::Monster(double max_health, double speed, MonsterType type, bool isBoss)
// {
//     this->max_health = max_health;
//     this->health_points = max_health;
//     this->speed = speed;
//     this->path_sprite = path_sprite;
//     this->type = type;
//     this->isBoss = isBoss;
//     this->isDead = false;
// }

// void Monster::find_path_sprite()
// {
//     switch (type)
//     {
//     case MonsterType::Zombie:
//         path_sprite = "";
//         break;

//     case MonsterType::Witch:
//         path_sprite = "";

//     case MonsterType::Skull:
//         path_sprite = "";

//     case MonsterType::Orc:
//         path_sprite = "";

//     default:
//         break;
//     }
// }

// void Monster::change_speed(float coeff)
// {
//     speed *= coeff;
// }

// void Monster::take_damage(float damage)
// {
//     health_points -= damage;
//     if (health_points <= 0)
//     {
//         isDead = true;
//     }
// }