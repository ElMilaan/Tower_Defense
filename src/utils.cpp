#include "utils.hpp"

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

GLfloat glNormalize(GLfloat coord, GLfloat mapSize)
{
    return static_cast<GLfloat>(2.0f * coord / mapSize - 1);
}

void draw_tile(Tile &tile, GLfloat mapSize)
{

    float x = glNormalize(tile.x, mapSize);
    float y = glNormalize(tile.y, mapSize);
    float size = 2.0f / mapSize;

    // cout << x << " , " << y << endl;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tile.texture);
    glTranslatef(x + size / 2, y + size / 2, 0.0f);
    glRotatef(tile.rotation, 0.0f, 0.0f, 1.0f);
    glTranslatef(-(x + size / 2), -(y + size / 2), 0.0f);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + size, y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + size, y + size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x, y + size);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}