#include "utils.hpp"

#include <iostream>
#include <filesystem>
#include <random>
#include "../../../../../../../../mingw64/include/c++/13.2.0/bits/stream_iterator.h" //include pour faire fonctionner le pc de Nolan le noob

using namespace std;

filesystem::path make_absolute_path(filesystem::path const &path, bool check_path_exists)
{
    auto const res{path.is_relative() ? CMAKE_SOURCE_DIR / path : path};

    if (check_path_exists && !filesystem::exists(res))
    {
        using namespace literals;
        auto const msg{"Path \""s + res.string() + "\" does not exist. Make sure you didn't misspell it or made it relative to the wrong folder. All relative paths will be relative to the directory containing your CMakeLists.txt file."};
        cerr << msg << '\n';
        throw runtime_error{msg};
    }

    return res;
}

int getDistanceBetweenTwoPoints(glm::vec2 p1, glm::vec2 p2)
{
    int a = (int)abs(p1.x - p2.x + p1.y - p2.y);
    return a;
}

glm::vec2 glNormalize(glm::vec2 pos, GLfloat mapSize, bool reverse)
{
    if (reverse)
    {
        return {2.0f * pos.x / mapSize - 1, 2.0f * pos.y / mapSize - 1};
    }
    return {2.0f * pos.x / mapSize - 1, -2.0f * pos.y / mapSize + 1};
}

vector<string> splitString(string str)
{
    stringstream ss(str);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> split_line(begin, end);
    return split_line;
}

static auto &generator()
{
    static default_random_engine gen{random_device{}()};
    return gen;
}

int random_int(int min, int max)
{
    uniform_int_distribution<int> distribution{min, max - 1};
    return distribution(generator());
}

double random_double(double min, double max)
{
    uniform_real_distribution<double> distribution{min, max};
    return distribution(generator());
}

void set_random_seed(int seed)
{
    generator().seed(seed);
}