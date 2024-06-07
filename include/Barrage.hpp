#include <iostream>

using namespace std;

enum class BarrageLocation
{
    First,
    Second,
    Third,
    Fourth
};

class Barrage
{
private:
    BarrageLocation location{};
    string sprite_path{};

public:
    BarrageLocation getLocation();
    string getSpritePath();
};