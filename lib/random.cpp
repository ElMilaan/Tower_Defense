#include "random.hpp"
#include <random>

using namespace std;

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

float random_float(float min, float max)
{
    uniform_real_distribution<float> distribution{min, max};
    return distribution(generator());
}

void set_random_seed(int seed)
{
    generator().seed(seed);
}