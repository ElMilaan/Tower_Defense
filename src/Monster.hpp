#include <iostream>

using namespace std;

enum class MonsterType
{
    Zombie,
    Witch,
    Skull,
    Orc,
};
class Monster
{
public:
    Monster(double health_points, double speed, MonsterType type, bool isBoss); // constructor
    void find_path_sprite();
    void change_speed(float coeff);
    void take_damage(float damage);

private:
    double max_health{};
    double health_points{};
    double speed{};
    MonsterType type{};
    string path_sprite{};
    bool isBoss{};
    bool isDead{};
};
