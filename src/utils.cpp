#include "../include/utils.hpp"

#include <iostream>
#include <filesystem>

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