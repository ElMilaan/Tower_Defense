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

double random_double(double min, double max)
{
    uniform_real_distribution<double> distribution{min, max};
    return distribution(generator());
}

void set_random_seed(int seed)
{
    generator().seed(seed);
}