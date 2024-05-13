// #include <iostream>
// #include "Tower.hpp"
// #include "Monster.hpp"
// #include <stack>
// #include "GLFW/glfw3.h"


// Tower::Tower(double range, double damage, double level, TowerType type, double construction_cost, double attack_speed)
// {
//     this->range = range;
//     this->damage = damage;
//     this->level = level;
//     this->attack_speed = attack_speed;
//     this->construction_cost = construction_cost;
//     this->type = type;
//     this->path_sprite = path_sprite;
// }

// void Tower::find_path_sprite()
// {
//     switch (type)
//     {
//     case TowerType::Fire:
//         path_sprite = "";
//         break;
//     case TowerType::Ice:
//         path_sprite = "";
//         break;
    
//     default:
//         break;
//     }
// }

// void Tower::level_up(float cost, float bank_sold)
// {
//     level += 1;
//     path_sprite = "";
//     // bank -= cost;
// }

// void Tower::build(vector<float> emplacement)
// {
    
// }

// void Tower::destruct()
// {
    
// }

// bool is_Monster_in_range(Monster monster)
// {
//     if (/*peut etre une fonction get_distance(monster, tower) <= this->range*/)
//     {
//         return 1;
//     }
//     else {
//         return 0;
//     }
    
// }
// void attack(Monster monster)
// {
//     // stack<Monster>file_attente_attaque{};
//     // if (is_Monster_in_range == 1)
//     // {
//     //     file_attente_attaque.push_back(monster);
//     // }
//     // while (file_attente_attaque.empty() == 0)
//     // {
//     //     file_attente_attaque.top
//     // }
    
//     while (is_Monster_in_range(monster) == 1 or monster.health_points != 0)
//     {
//         double Time{glfwGetTime() * Tower->attack_speed};
        
        
//         monster.health_points -= Tower->damage; 
//     }
    
// }