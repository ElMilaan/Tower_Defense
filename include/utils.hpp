#pragma once

#include <filesystem>
#include <glm/glm.hpp>
#include "Tile.hpp"

using namespace std;

filesystem::path make_absolute_path(filesystem::path const &path, bool check_path_exists = true);

template <glm::length_t N, typename T, glm::qualifier Q>
ostream &operator<<(ostream &os, glm::vec<N, T, Q> const &vec)
{
    os << "(";

    os << vec[0];
    for (size_t i{1}; i < N; ++i)
    {
        os << ", " << vec[i];
    }
    os << ")";
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, vector<T> const &vec)
{
    if (vec.empty())
    {
        return os << "[]";
    }

    os << '[';
    for (size_t i{0}; i < vec.size() - 1; ++i)
    {
        os << vec[i] << ", ";
    }
    return os << vec.back() << ']';
}

int getDistanceBetweenTwoPoints(glm::vec2 p1, glm::vec2 p2);
glm::vec2 glNormalize(glm::vec2 pos, GLfloat mapSize, bool reverse);

vector<string> splitString(string str);

/* ------------------ RANDOM ------------------ */

int random_int(int min, int max);
double random_double(double min, double max);
void set_random_seed(int seed);